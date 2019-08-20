#include <xc.h>
#define _XTAL_FREQ 4000000L

void InitSystem(void);
int main(void)
{
    OSCCONbits.IRCF = 0b110;
    ADCON0 = 0x00;  //Disable ADC
    ADCON1 = 0xFF;  //Set PORTB to be digital instead of analog default  
    InitSystem();
    while(1)
    {
        PORTB=0x0F;
        __delay_ms(500);    
        PORTB=0x00;
        __delay_ms(500);   
    }
}
void InitSystem(void)
{
    PORTB = 0x00;  //initialize PORTB register
    TRISB = 0xF0;  //set RB0-RB3 as outputs and RB4-RB7 as inputs
}
/********************************************************************************
|  CLASS:         Getting Started with MPLAB XC compilers
|  PROGRAM:       Lab2.c   
|  AUTHOR:        Mark Reynolds
|  DATE:          May 2013
|  DESCRIPTION:   Set configuration bits in code, check result in configuration
|                 bits window.
|  REQUIREMENTS:                   
| 
|  REVISION HISTORY:
|  Jan 2013       Mark Reynolds modified for XC8 v1.10
|  Dec 2012       Mark Reynolds Updated for XC16 v1.10
|  20 JAN 2008    Rob Ostapiuk
|                 First Draft
********************************************************************************/