#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H


/**
 * @param:     none
 * @return:    none
 * @comment:   This macro will enable global interrupts.
 * @usage:     INTERRUPT_GlobalalInterruptEnable();
 */
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

/**
 * @param:     none
 * @return:    none
 * @comment:   This macro will disable global interrupts.
 * @usage:     INTERRUPT_GlobalInterruptDisable();
 */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

/**
 * @param:     none
 * @return:    none
 * @comment:   This macro will enable peripheral interrupts.
 * @usage:     INTERRUPT_PeripheralInterruptEnable();
 */
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

/**
 * @param:     none
 * @return:    none
 * @comment:   This macro will disable peripheral interrupts.
 * @usage:     INTERRUPT_PeripheralInterruptDisable();
 */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

/**
 * @prototype: interrupt void interruptManager (void)
 * @param:     none
 * @return:    none
 * @comment:   Main interrupt service routine. Calls module interrupt handlers.
 * @usage:     interruptManager();
 */
void interrupt INTERRUPT_Interrupthandler(void);

#endif  // interrupt_handler.h
