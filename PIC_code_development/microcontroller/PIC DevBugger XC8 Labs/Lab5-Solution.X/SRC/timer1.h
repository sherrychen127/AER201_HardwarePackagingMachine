#ifndef timer1_H
#define timer1_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t timer_size_t;
typedef uint16_t timer_size_t;
 
/*****************************************************************************
 * This initializer configure the Timer control registers.
 * @Prototype  void TIMER1_initializerDefault (void)
 * @Param      parameters required to initialize timer
 *              T1CONvalue  is the hex configuration number to load into T1CON
 *              T1GCONvalue is the hex configuration number to load into T1GCON
 *              TMR1Hvalue is the upper byte of the initial load for TMR1
 *              TMR1Lvalue is the lower byte of the initial load for TMR1
 *              T1INTValue is 1 to enable the interrupt, 0 to disable
 * @Return     none
 * @Comment    
 * @Usage      TIMER1_initializerDefault();
*****************************************************************************/
void TIMER1_initializer (char T1CONvalue,char TMR1Hvalue,char TMR1Lvalue,char T1INTvalue);

/*****************************************************************************
 * This routine starts the timer
 * @Prototype 	void TIMER1_StartTimer (void)
 * @Param     	none
 * @Return    	none
 * @Usage       TIMER1_StartTimer function();
*****************************************************************************/
void TIMER1_StartTimer (void);

/*****************************************************************************
 * This routine stops the timer
 * @Prototype 	void TIMER1_StopTimer (void)
 * @Param     	none
 * @Return    	none
 * @Usage       TIMER1_StopTimer();
*****************************************************************************/
void TIMER1_StopTimer (void);

/*****************************************************************************
 * This rouitne reads the Timer register value 
 * @Prototype 	uint16_t TIMER1_ReadTimer (void)
 * @Param     	none
 * @Return    	TIMER1_ ReadTimer  at the time of the function call
 *              read as a 16-bit value
 * @Usage       TIMER1_ ReadTimer();
*****************************************************************************/
uint16_t TIMER1_ReadTimer (void);

/*****************************************************************************
 * This routine writes to Timer register
 * @Prototype 	void TIMER1_WriteTimer (uint16_t TimerVal)
 * @Param     	uint_var - 16-bit TIMER1_WriteTimer
 * @Return    	none
 * @Usage       TIMER1_WriteTimer (uint16_t TimerVal);
*****************************************************************************/
void TIMER1_WriteTimer (uint16_t TimerVal);

/*****************************************************************************
 * Boolean routine to poll or to check for the overflow flag on the fly
 * @Prototype 	bool TIMER1_IsOverflowOccured (void)
 * @Param  	none
 * @Return	Timeroverflow or no timer overflow
 * @Usage       TIMER1_IsOverflowOccured(void)
*****************************************************************************/
bool TIMER1_IsOverflowOccured (void);

/*****************************************************************************
 * Timer Interrupt Service Routine. Called by the Interrupt Manager. <br>Place your Timer Interrupt code here. </br>
 * @Protoype  void timer1_ISR (void)
 * @Param     none
 * @Output    none
 * @Return    none
 * @Usage     TIMER1_ISR();
 *****************************************************************************/
 void TIMER1_ISR (void);

/*****************************************************************************
 * CallBack function.Called by the Interrupt Manager. <br>CallBack code here. </br>
 * @Protoype  void TIMER1_CallBack (void)
 * @Param     none
 * @Output    none
 * @Return    none
 * @Usage     TIMER1_ISR();
 *****************************************************************************/
 void TIMER1_CallBack (void);
 
 #endif // TIMER1.h