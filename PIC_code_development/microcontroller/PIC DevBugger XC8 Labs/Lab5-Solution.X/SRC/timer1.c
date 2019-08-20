#include <xc.h>
#include "TIMER1.h"
#include "interrupt_handler.h"

/*******************************************************************************
 * Prototype:   void TIMER1_initializer (void)
 * Input:       none
 * Output:      none
 * Description: custom init function for Timer1
 * Comment:     
 * Usage:       TIMER1_initializer ();
 ***************************************************************************/
void TIMER1_initializer (char T1CONvalue,char TMR1Hvalue,char TMR1Lvalue,char T1INTvalue){
    // set the Timer to the options selected in the GUI
    // Peripheral Code Generator

    T1CON = T1CONvalue;
    // set the Timer to the options selected in the GUI
    // Peripheral Code Generator

    TMR1H = TMR1Hvalue;
    // set the Timer to the options selected in the GUI
    // Peripheral Code Generator

    TMR1L = TMR1Lvalue;
    
    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Enabling TIMER1 interrupt.
    if (T1INTvalue)
    {
        PIE1bits.TMR1IE = 1;
        INTERRUPT_PeripheralInterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
    }
  }

/****************************************************************************
 * Prototype:   void TIMER1_StartTimer (void)
 * Input:       none
 * Output:	none
 * Description: TIMER1_StartTimer function.
 * Usage:       TIMER1_StartTimer();
 ****************************************************************************/
void TIMER1_StartTimer (void)
{
    //Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON=1;
}

/****************************************************************************
 * Prototype:   void TIMER1_StopTimer (void)
 * Input:       none
 * Output:	none
 * Description: TIMER1_StopTimer /close function.
 * Usage:       TIMER1_StopTimer (void)();
 ****************************************************************************/
void TIMER1_StopTimer (void)
{
    //Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON=0;
}

/****************************************************************************
 * Prototype:   uint16_t TIMER1_ReadTimer (void)
 * Input:       none
 * Output:	TIMER1_ReadTimer  at the time of the function call
 *              read as a 8-bit value
 * Description: TIMER1_ReadTimer function
 * Usage:       TIMER1_ReadTimer();
 ****************************************************************************/
uint16_t TIMER1_ReadTimer (void)
{
    uint16_t ReadVal;

    ReadVal = TMR1;
    return ReadVal;
}

/****************************************************************************
 * Prototype:   void TIMER1_WriteTimer (uint16_t TimerVal)
 * Input:       uint- 16-bit TIMER1_WriteTimer
 * Output:	none
 * Description: TIMER1_WriteTimer function
 * Usage:       TIMER1_WriteTimer(uint16_t TimerVal);
 ****************************************************************************/
void TIMER1_WriteTimer (uint16_t TimerVal)
{	
    if (T1CONbits.nT1SYNC == 1)
	{
            //Write to the Timer register
            TMR1L = TimerVal>> 8;
            TMR1H = TimerVal;
	}	
	else     
	{	
            //Stop the Timer by writing to TMRxON bit
            T1CONbits.TMR1ON=0;

            //Write to the Timer register
            TMR1L = TimerVal>> 8;
            TMR1H = TimerVal;
	}	
}

/****************************************************************************
 * Prototype:   bool TIMER1_IsOverflowOccured (void)
 * Input: 	none 
 * Output: 	Timeroverflow or no timer overflow
 * Description: Boolean routine to poll or to check for the overflow flag on the fly
 * Usage:       TIMER1_IsOverflowOccured(void)
 ************************************************************************************/
bool TIMER1_IsOverflowOccured (void)
{
       
    //check if  overflow has occured by checking the TMRIF bit
    return(!PIR1bits.TMR1IF);
}  

/*******************************************************************************
 * Prototype:	void timer1_ISR (void)
 * Input:	none
 * Output:	none
 * Description:	TIMER1 Interrupt Service Routine.Called by the
 *              Interrupt Manager.Place your TIMER1
 *              Interrupt code here.
 * Usage:	timer1_ISR ();
 ******************************************************************************/
void TIMER1_ISR (void)
{
    if(PIR1bits.TMR1IF)
    {
        volatile unsigned int CountCallBack = 0;

        {
            // ticker function call
            TIMER1_CallBack();

            // reset ticker counter
            CountCallBack = 0;
        }
	// add your Timer1 interrupt custom code
	// clear the Timer1 interrupt flag
	PIR1bits.TMR1IF = 0;
    }
}

/*******************************************************************************
 * Prototype:	void TIMER1_CallBack (void)
 * Input:	none
 * Output:	none
 * Description:	TIMER1 CallBack function. 
 *              Called by the TIMER1 interrupt handler.
 *              Place your TIMER1 CallBack code here. 
 * Usage:	timer1_ISR ();
 ******************************************************************************/
void TIMER1_CallBack (void)
{
    LATBbits.LATB0 ^= 1;// Add your custom callback code here
}