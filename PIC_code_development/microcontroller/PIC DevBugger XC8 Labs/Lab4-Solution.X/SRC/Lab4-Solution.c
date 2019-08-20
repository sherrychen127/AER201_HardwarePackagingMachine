/*-------------------------------------------------------------------------------
  HEADER FILES
-------------------------------------------------------------------------------*/
#include <xc.h>           // generic device include file

/*-------------------------------------------------------------------------------
  PROGRAM CONSTANTS
-------------------------------------------------------------------------------*/
// None

/*-------------------------------------------------------------------------------
  VARIABLE DECLARATIONS
-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------
  FUNCTION PROTOTYPES
-------------------------------------------------------------------------------*/
void InitSystem(void);
void Interrupt_initializer(void);
void TIMER1_initializer(void);

/*===============================================================================
  FUNCTION:     interrupt Timer1_ISR()
  DESCRIPTION:  Re-load Timer1 and toggle bits on PORTB
  PARAMETERS:   none
  RETURNS:      nothing
  REQUIREMENTS: none
===============================================================================*/
void __interrupt INTERRUPT_Interrupthandler (void)
{
	PIR1bits.TMR1IF = 0;                //clear TMR1IF to enable further interrupts
	TMR1H = 0X3C;                       //re-load the Timer1 register pair (TMR1H:TMR1L)
                                            //with 15536 (3CB0 hex)
	TMR1L = 0XB0;
        LATBbits.LATB0 = LATBbits.LATB0 ^ 1;//Toggle bit 0 in PORTB
}

/*===============================================================================
  FUNCTION:     main()
  DESCRIPTION:  Initialize the interrupt control register (INTCON).
                Enable Global and External interrupts and wait.
  PARAMETERS:   none
  RETURNS:      nothing
  REQUIREMENTS: none
===============================================================================*/
void main(void)
{
    InitSystem();           //initialize PORTB
    TIMER1_initializer();          //initialize Timer1 registers
    Interrupt_initializer();      //setup Timer 1 interrupts
    T1CONbits.TMR1ON = 1;   //Turn on Timer 1
    while(1);               //Sit here and wait for interrupts
}

/*===============================================================================
  FUNCTION:     init_PORTB()
  DESCRIPTION:  Initializes PORTB
  PARAMETERS:   none
  RETURNS:      nothing
  REQUIREMENTS: none
===============================================================================*/
void InitSystem(void)
{
	PORTB = 0X00;  //initialize PORTB register
	TRISB = 0XF0;  //set RB0-RB3 as outputs and RB4-RB7 as inputs
    ADCON0 = 0x00;  //Disable ADC
    ADCON1 = 0xFF;  //Set PORTB to be digital instead of analog default  
}

/*===============================================================================
  FUNCTION:     init_Timer1()
  DESCRIPTION:  Initializes Timer1
  PARAMETERS:   none
  RETURNS:      nothing
  REQUIREMENTS: none
===============================================================================*/
void TIMER1_initializer(void)
{
	T1CONbits.TMR1ON = 0;           //make sure Timer1 is off
	TMR1H = 0x00;                   //### Set TMR1H to 0x00
	TMR1L = 0x00;                   //### Set TMR1L to 0x00
	T1CONbits.TMR1CS = 0;           //### Set clock source to Fosc/4 (TMR1CS)
	T1CKPS0 = 1;                    //### set Timer1 Pre-scale to 8 using
	T1CKPS1 = 1;                    //### T1CKPS0 and T1CKPS1
}

/*===============================================================================
  FUNCTION:     init_interrupts()
  DESCRIPTION:  Initializes interrupts
  PARAMETERS:   none
  RETURNS:      nothing
  REQUIREMENTS: none
===============================================================================*/
void Interrupt_initializer(void)
{
	PIR1bits.TMR1IF = 0;                 //clear TMR1IF
	PIE1bits.TMR1IE = 1;                 //### Enable Timer 1 Interrupts
	INTCONbits.PEIE = 1;                 //### Enable Peripheral Interrupts
	INTCONbits.GIE = 1;                  //### Enable Global Interrupts
}
/********************************************************************************
|  CLASS:         Getting Started with MPLAB XC8
|  PROGRAM:       Lab4.c   
|  AUTHOR:        Mark Reynolds
|  DATE:          Feb 2013
|  DESCRIPTION:   Write an interrupt service routine to handle the T1 interrupt
|  REQUIREMENTS:                  
| 
|  REVISION HISTORY:
|   Feb 2013    Mark Reynolds  Initial Release

|  
********************************************************************************/