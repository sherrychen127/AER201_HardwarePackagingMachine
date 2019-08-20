/*
 * File:   main.c
 * Author: Michael Ding
 * version: 1.0
 * 
 * Description: Demonstrates the use of the Analog to Digital Converter (ADC)
 *              module in the PIC.
 *              break_beam sensor
 * Preconditions:
 *   1. Jumpers JP5 and JP4 are shorted
 *   2. Character LCD is in a PIC socket
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"

/**** Local function prototypes *****/
unsigned short readADC(char channel);
int counter = 0;
int mode = 1;

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    /*FOSC3 = 0;
    FOSC2 = 1;
    FOSC1 = 1;
    FOSC0 = 0;
    
    /*
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCTUNEbits.PLLEN = 1; //PLL enabled for INTOSC
    
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
    ADCON1 = 0x0B;  // RA0-3 are analog (pg. 222)
    ADCON2bits.ADFM = 1; // Right justify A/D result

    
    //if (mode == 1){
    /*
        while(1) {
            initLCD();
            printf("RA1: %.3x", readADC(11));
            __delay_ms(200);
            __lcd_home();
            //__delay_ms(300);
            if (readADC(11)>250){       // original circuit = 150
            
                counter++;
                //initLCD();
                //printf("%d",counter);
                //__delay_ms(20);
                //__lcd_home();
                }
            }
        initLCD();
        __lcd_home();
       

       //__lcd_newline();
       //printf("RA3: %.3x", readADC(3));
       
       //__delay_ms(400);
        
    //}
        */

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
