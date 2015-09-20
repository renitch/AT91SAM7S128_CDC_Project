//*--------------------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*--------------------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*--------------------------------------------------------------------------------------
//* File Name           : main file
//* Object              :
//* Translator          :
//* 1.0 02/Mar/05 JPP	: Creation
//*--------------------------------------------------------------------------------------

#include "project.h"
#include "cdc_enumerate.h"

#define MSG_SIZE 				1000

static unsigned int wifi_CH_PD = AT91C_PIO_PA30;
static unsigned int wifi_RST = AT91C_PIO_PA29;
static unsigned int wifi_GPIO2 = AT91C_PIO_PA4;
static unsigned int wifi_GPIO0 = AT91C_PIO_PA27;

//* external function

extern void Usart_init ( void );
extern void AT91F_US_Put( char *buffer); // \arg pointer to a string ending by \0
extern void Trace_Toggel_LED( unsigned int led) ;

struct _AT91S_CDC 	pCDC;

//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_Open
//* \brief This function Open the USB device
//*----------------------------------------------------------------------------
void AT91F_USB_Open(void)
{
    // Set the PLL USB Divider
    AT91C_BASE_CKGR->CKGR_PLLR |= AT91C_CKGR_USBDIV_1 ;

    // Specific Chip USB Initialisation
    // Enables the 48MHz USB clock UDPCK and System Peripheral USB Clock
    AT91C_BASE_PMC->PMC_SCER = AT91C_PMC_UDP;
    AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_UDP);

    // Enable UDP PullUp (USB_DP_PUP) : enable & Clear of the corresponding PIO
    // Set in PIO mode and Configure in Output
    AT91F_PIO_CfgOutput(AT91C_BASE_PIOA,AT91C_PIO_PA16);
    // Clear for set the Pul up resistor
    AT91F_PIO_ClearOutput(AT91C_BASE_PIOA,AT91C_PIO_PA16);

    // CDC Open by structure initialization
    AT91F_CDC_Open(&pCDC, AT91C_BASE_UDP);
}

//*--------------------------------------------------------------------------------------
//* Function Name       : main
//* Object              :
//*--------------------------------------------------------------------------------------
int main ( void )
{
	char data[MSG_SIZE];
	unsigned int length;
     // Enable User Reset and set its minimal assertion to 960 us
     AT91C_BASE_RSTC->RSTC_RMR = AT91C_RSTC_URSTEN | (0x4<<8) | (unsigned int)(0xA5<<24);
   // Led init
   // First, enable the clock of the PIOB
     AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_PIOA ) ;
   //* to be outputs. No need to set these pins to be driven by the PIO because it is GPIO pins only.
     AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, AT91B_LED_MASK ) ;
   //* Clear the LED's.
    AT91F_PIO_SetOutput( AT91C_BASE_PIOA, AT91B_LED_MASK ) ;
   //* Set led 1e LED's.
    AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, AT91B_LED1 ) ;

     AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, wifi_CH_PD ) ;
     AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, wifi_RST ) ;
     AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, wifi_GPIO2 ) ;
     AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, wifi_GPIO0 ) ;

     AT91F_PIO_SetOutput( AT91C_BASE_PIOA, wifi_RST ) ;
     AT91F_PIO_SetOutput( AT91C_BASE_PIOA, wifi_GPIO2 ) ;
     AT91F_PIO_SetOutput( AT91C_BASE_PIOA, wifi_GPIO0 ) ;
     AT91F_PIO_SetOutput( AT91C_BASE_PIOA, wifi_CH_PD ) ;

    // Init USB device
    AT91F_USB_Open();
    // Init USB device
    // Wait for the end of enumeration
    while (!pCDC.IsConfigured(&pCDC));
  //* Set led 1e LED's.
    AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, AT91B_LED1 ) ;
    // Set Usart in interrupt
    Usart_init();
   //* Set led all LED's.
    AT91F_PIO_ClearOutput( AT91C_BASE_PIOA, AT91B_LED_MASK ) ;

    while (1)
   {       // Loop
	  length = pCDC.Read(&pCDC, data, MSG_SIZE);
	  data[length]=0;
	  Trace_Toggel_LED( AT91B_LED1) ;
          AT91F_US_Put(data);
   }
}


