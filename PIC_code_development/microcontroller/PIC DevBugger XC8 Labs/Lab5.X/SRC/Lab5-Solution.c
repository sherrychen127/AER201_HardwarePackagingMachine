#include <xc.h>
#include "CLKconfig.h"
#include "interrupt_handler.h"
#include "timer1.h"
void InitSystem(void);
/****************************************************************************
 *
 *                        Main application
 *
****************************************************************************/
void main(void)
{
    // initialize the device
    InitSystem();
    TIMER1_initializer (0x34,0x00,0x00,1);
    TIMER1_StartTimer();
    while (1);
}
/****************************************************************************
 *
 * Prototype:       void InitSystem (void)
 *
 * Input:           none
 * Output:	    none
 * Description:     Initize the Oscillator and I/O pins needed
 * Usage:           InitSystem();
 *
 ***************************************************************************/
void InitSystem(void)
{
    OSCCON = 0x6B;
    TRISB = 0xF0;
    LATB = 0x00;
}
/****************************************************************************
 *
 * Prototype:       interrupt void INTERRUPT_Interrupthandler (void)
 *
 * Input:           none
 * Output:	    none
 * Description:     Main interrupt service routine. Calls module interrupt handlers.
 * Usage:           INTERRUPT_Interrupthandler();
 *
 ***************************************************************************/
void __interrupt Interrupthandler (void)
{
    // timer1 interrupt handler
    TIMER1_ISR();
}