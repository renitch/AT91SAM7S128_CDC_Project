#ifndef _GPS_TIME_H
#define _GPS_TIME_H

typedef struct _DateTime
{
	// Private members
	unsigned int hour;
	unsigned int minute;
	unsigned int sec;
	unsigned int day;
	unsigned int month;
	unsigned int year;
} DateTime;

void analyseBufferForRMC(const char *pData, unsigned int length);
unsigned int DayOfWeek (unsigned int day, unsigned int month, unsigned int year);
unsigned int IsLeapYear (unsigned int year);
void SunTime(DateTime *dt, signed char zone);
unsigned int MonthDay(unsigned int month, unsigned int year);
void getFormattedString(DateTime *dt, char * buf, unsigned int * length);

#endif