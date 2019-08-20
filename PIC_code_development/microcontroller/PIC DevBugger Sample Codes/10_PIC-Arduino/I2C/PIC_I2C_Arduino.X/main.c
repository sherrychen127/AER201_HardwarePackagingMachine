 /*
 * File:   main.c
  * Sherry Chen
 
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "I2C.h"

/***** Constants *****/
const char keys[] = "123A456B789C*0#D";

void main(void) {

    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /********************************* PIN I/O ********************************/
    OSCCON = 0xF2;
    
    /*
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
     */
    OSCTUNEbits.PLLEN = 1; //PLL enabled for INTOSC
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
    TRISC = 0b10000000; /* RC3 is SCK/SCL (SPI/I2C),
                         * RC4 is SDA (I2C),
                         * RC5 is SDA (SPI),
                         * RC6 and RC7 are UART TX and RX, respectively. */
    TRISD = 0x00; // All output mode on port D for the LCD
    TRISE = 0x00;
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    // </editor-fold>
    
    /* Initialize LCD. */
    initLCD();  

    /* Initialize I2C Master with 100 kHz clock. */
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    

    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
    /* Initialize local variables. */
    unsigned char mem[3]; // Initialize array to check for triple-A sequence
    unsigned char counter = 0; // Increments each time a byte is sent
    unsigned char keypress; // Stores the data corresponding to the last key press
    unsigned char data; // Holds the data to be sent/received
    static bit SEND;
    SEND = 1;
    
    /* Main loop. */
    while(1) {
        
        
        
            
            I2C_Master_Start(); // Start condition
            I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
            I2C_Master_Write('1'); // Write key press data
            I2C_Master_Stop();

            //__delay_ms(1000);
            
            I2C_Master_Start(); // Start condition
            I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
            I2C_Master_Write('2'); // Write key press data
            I2C_Master_Stop();
            //__delay_ms(1000);
        }
      
    
}
