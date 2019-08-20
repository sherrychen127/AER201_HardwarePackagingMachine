/*
 * File:   main.c
 * Author: Michael Ding
 *
 * Created on July 18, 2016, 12:11 PM
 * 
 * Edited by Tyler Gamvrelis, summer 2017
 * 
 * Description: Demonstration of interrupt on change feature of RB1. The main
 *              loop changes the characters displayed on the top line of the 
 *              LCD, while the interrupt handler displays key press data on the
 *              bottom line.
 * 
 * Preconditions:
 *   1. Character LCD in a PIC socket
 *   2. Co-processor is running default keypad encoder program
 */


/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"

/***** Constants *****/
const char keys[] = "123A456B789C*0#D"; 

unsigned short readADC(char channel);
int W_count=0;

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    OSCCON = 0xF2;
    /*
    
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCTUNEbits.PLLEN = 1;
     * 
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
    ADCON2bits.ADFM = 1;
    // </editor-fold>
    
    //INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    
    /* Initialize LCD. */
    initLCD();
    
    
    
    LATCbits.LATC0 = 1;  //set RC0 HIGH-> disable KPD
    TRISCbits.RC0 = 0;
    
    
    while(1){
        if (readADC(11)<320){
            W_count++;
            
        }
        initLCD();
        printf("%d",W_count);
        __lcd_home();
        
    }
    
    
    //INT1IE = 0;
    //RBIE = 1;  //set RBIE port B      //uncomment this for interrupt
    //PEIE = 1;  //allow peripheral interrupt
    W_count = 0;
    printf("%d",W_count);
    initLCD();
    
    /*
    while(1){
        printf("%d",W_count);
        if(W_count >= 4){
            //break;
        }
        __delay_ms(1000);
        __lcd_home();
 
    }
    initLCD();
    RBIE = 0; 
    while(1){
        
        printf("%d",W_count);
        __delay_ms(3000);
        __lcd_home();
    }
     */ 
    

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
    
    if (RBIF){
        initLCD();
        printf("W_count:%d",W_count);
        //printf("interrupted");
        //printf("RB4: %.3x", readADC(11));
        if (readADC(11)<= 300){
            W_count++;
            initLCD();
            
            printf("W_count:%d",W_count);
            //__delay_ms(100);
            //printf("interrupted");
        }
        RBIF = 0;
    }
    
}



unsigned short readADC(char channel){
    /* Reads the analog input from the specified analog channel.
     *
     * Arguments: channel, the byte corresponding to the channel to read
     *
     * Returns: the 10-bit value corresponding to the voltage read from
     *          the specified channel
     */
    
    ADCON0 = (channel & 0x0F) << 2; // Select ADC channel (i.e. pin)
    ADON = 1; // Enable module
    ADCON0bits.GO = 1; // Initiate sampling
    while(ADCON0bits.GO_NOT_DONE){  continue;   } // Poll for acquisition completion
    return (ADRESH << 8) | ADRESL; // Return result as a 16-bit value
}

