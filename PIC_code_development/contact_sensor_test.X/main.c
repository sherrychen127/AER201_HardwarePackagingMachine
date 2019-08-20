

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"

/***** Constants *****/
const char keys[] = "123A456B789C*0#D"; 
const char array[] = "10";
void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /********************************* PIN I/O ********************************/
    /* Write outputs to LATx, read inputs from PORTx. Here, all latches (LATx)
     * are being cleared (set low) to ensure a controlled start-up state. */  
    LATA = 0x00;
    LATB = 0x00; 
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;

    /* After the states of LATx are known, the data direction registers, TRISx
     * are configured. 0 --> output; 1 --> input. Default is  1. */
    TRISA = 0xFF; // All inputs (this is the default, but is explicated here for learning purposes)
    TRISB = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00; // All output mode on port D for the LCD
    TRISE = 0x00;
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    // </editor-fold>
    
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    
    /* Initialize LCD. */
    initLCD();
    while(1){
        TRISAbits.RA4 = 1; //RA0
        unsigned char input = PORTAbits.RA4;
        //printf("input:");
        putch(array[input]);
        __delay_ms(500);
        __lcd_home();
    }
    
    
}

void interrupt interruptHandler(void){
    /* This function is mapped to the interrupt vector, and so is called when
     * any interrupt occurs to handle it. Note that if any interrupt is enabled,
     * and it does not have a handler to clear it, then unexpected behavior will
     * occur, perhaps even causing the PIC to reset.
     *
     * Arguments: none
     * 
     * Returns: none
     */
    
    if(INT1IF){
        /* Interrupt on change handler for RB1. */
        
        /* Write key press data to bottom line of LCD. */
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        putch(keys[keypress]);
        __lcd_home();
        
        INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
    }
}


