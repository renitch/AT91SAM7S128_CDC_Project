#include "project.h"

#include "gps_time.h"
#include "cdc_enumerate.h"

extern struct _AT91S_CDC 	pCDC;

static char time_buffer[200];
static unsigned int startedLine = 0;
static unsigned int timeBufferIndex = 0;
static unsigned int UTC_OFFSET = 2;
DateTime gpsTime;

void analyseBufferForRMC(const char *pData, unsigned int length){
	for(int i = 0; i < length; i++){
		if(pData[i] == '$'){
			startedLine = 1;
			timeBufferIndex = 0;
		}
		if(pData[i] == 10 || pData[i] == 13){
			startedLine = 0;
			time_buffer[timeBufferIndex++]=13;
			time_buffer[timeBufferIndex++]=10;

			if(	time_buffer[0]=='$' && 
				time_buffer[1]=='G' &&
				time_buffer[2]=='P' &&
				time_buffer[3]=='R' &&
				time_buffer[4]=='M' &&
				time_buffer[5]=='C'){
				//pCDC.Write(&pCDC, time_buffer,timeBufferIndex);
				unsigned int j = 0;
				int got_hour;
				int got_min;
				int got_sec;
				int got_day;
				int got_month;
				int got_year;
				while(time_buffer[j++] != ',');
				got_hour = (time_buffer[j]-'0')*10 +  (time_buffer[j+1]-'0');
				got_min = ((time_buffer[j+2]-'0')*10)+(time_buffer[j+3]-'0');
				got_sec = ((time_buffer[j+4]-'0')*10)+(time_buffer[j+5]-'0');
				j+=6;
				while(time_buffer[j++] != ',');
				while(time_buffer[j++] != ',');
				while(time_buffer[j++] != ',');
				while(time_buffer[j++] != ',');
				while(time_buffer[j++] != ',');
				while(time_buffer[j++] != ',');
				while(time_buffer[j++] != ',');
				while(time_buffer[j++] != ',');
				got_day = ((time_buffer[j]-'0')*10)+(time_buffer[j+1]-'0');
				got_month = ((time_buffer[j+2]-'0')*10)+(time_buffer[j+3]-'0');
				got_year = ((time_buffer[j+4]-'0')*10)+(time_buffer[j+5]-'0');

				gpsTime.day = got_day;
				gpsTime.month = got_month;
				gpsTime.year = (got_year >= 80) ? got_year + 1900 : got_year + 2000;
				gpsTime.hour = got_hour;
				gpsTime.minute = got_min;
				gpsTime.sec = got_sec;

				SunTime(&gpsTime, UTC_OFFSET);

				getFormattedString(&gpsTime, time_buffer, &j);

				pCDC.Write(&pCDC, time_buffer, j);
			}
			timeBufferIndex = 0;
		}
		if(startedLine == 1)time_buffer[timeBufferIndex++]=pData[i];
	}
}

void getFormattedString(DateTime *dt, char * buf, unsigned int * length){
	buf[0] = dt->hour / 10 + '0';
	buf[1] = dt->hour % 10 + '0';
	buf[2] = ':';
	buf[3] = dt->minute / 10 + '0';
	buf[4] = dt->minute % 10 + '0';
	buf[5] = ':';
	buf[6] = dt->sec / 10 + '0';
	buf[7] = dt->sec % 10 + '0';
	buf[8] = ' ';
	buf[9] = dt->day / 10 + '0';
	buf[10] = dt->day % 10 + '0';
	buf[11] = '.';
	buf[12] = dt->month / 10 + '0';
	buf[13] = dt->month % 10 + '0';
	buf[14] = '.';
	buf[15] = dt->year % 1000;
	buf[16] = (dt->year % 1000) / 100 + '0';
	buf[17] = (dt->year % 100) / 10 + '0';
	buf[18] = dt->year % 10 + '0';
	buf[19] = 13;
	buf[20] = 10;

	*length = 21;
}

unsigned int MonthDay(unsigned int month, unsigned int year){
  if(month == 1)return 31;
  else if (month == 2 && IsLeapYear(year) != 0 ) return 29;
  else if (month == 2 && IsLeapYear(year) == 0 ) return 28;
  else if (month == 3) return 31;
  else if (month == 4) return 30;
  else if (month == 5) return 31;
  else if (month == 6) return 30;
  else if (month == 7) return 31;
  else if (month == 8) return 31;
  else if (month == 9) return 30;
  else if (month == 10) return 31;
  else if (month == 11) return 30;
  else if (month == 12) return 31;
  else return 0;
}

void SunTime (DateTime *dt, signed char zone){
	char M, O;

	// Ќаходим последнее воскресенье марта и последнее воскресенье окт€бр€
	M = 31 - DayOfWeek(31,3,dt->year);
	O = 31 - DayOfWeek(31,10,dt->year);

	// ”чЄт летнего времни (с последнего воскресень€ марта до последнего воскресень€ окт€бр€)
	if (((dt->month > 3)   && (dt->month < 10)) ||
      	((dt->month == 3)  && (dt->day >= M) && (dt->hour >= 0))   ||
      	((dt->month == 10) && (dt->day <= O) && (dt->hour <= 1)))
	zone++;

	if ((dt->hour + zone) < 24)
		dt->hour += zone;
	else{
		dt->hour = dt->hour + zone - 24;

		if ((dt->day + 1) <= MonthDay(dt->month, dt->year))
			dt->day++;
		else{
			dt->day = 1;

			if ((dt->month + 1) <= 12)
				dt->month++;
			else{
				dt->month = 1;
				dt->year++;
			}
		}
	}
}

unsigned int IsLeapYear (unsigned int year){
	return ((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0));
}

unsigned int DayOfWeek (unsigned int day, unsigned int month, unsigned int year){
	unsigned int a = (14 - month) / 12;
	unsigned int y = year - a;
	unsigned int m = month + 12 * a - 2;

	return (7000 + (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7;
}