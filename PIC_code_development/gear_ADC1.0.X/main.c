/*
 * File:   main.c
 * Author: Sherry Chen
 *
 * Created on July 18, 2016, 12:11 PM
 *
 * Updated by Tyler Gamvrelis on July 28, 2017, 9:06 PM
 * 
 * Description: Rotate 360 degrees and then stop
 * 
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
int prev = 0;
int i;

unsigned short readADC(char channel);

void servoRotate_clockwise(){
      //PORTB as output
    for (i = 0; i<1; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(1400); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(18600);
    }
    //clockwise;
    
}

void servoRotate_ConStop(){   //stop
    for(i=0;i<50;i++)
    {
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(1500); // pulse of 1500us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(18500);
    }
}


void servoRotate_counter(){    //counterclockwise
      //PORTB as output
    for (i = 0; i<1; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(2200); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(17800);
    }
    //clockwise;
    
}

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    OSCCON = 0xF2;  // Use 8 MHz internal oscillator block
    
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
    //</editor-fold>
    
    /* Initialize character LCD. */
    initLCD();
    
    
    
        while(1) {
        //__lcd_clear();
        //__lcd_home();
        //initLCD();
        
           
         
            servoRotate_clockwise();
        
        }
       /* Print results to character LCD. Since ADC results are 10 bits, they
        * are split up into two registers ADRESH and ADRESL. The results of the
        * ADC are displayed in hexadecimal so that the values in each of these
        * registers will be easily visible; ADRESL corresponds to the two least
        * significant digits, while ADRESH corresponds to the most significant 
        * bit. */
            if (counter == 40){
               
            }
            if (readADC(3)<250)
            {       // original circuit = 150
                if (prev == 0){
                    initLCD();
                    printf("%d",counter);
                    __lcd_home();
                    //__delay_ms();
                    counter++;
                    prev = 1;
                }
                
                
            }
            else{
                    prev = 0;
            }
        
        
        //__delay_ms(500);
       
       
       //printf("RA0: %.3x", readADC(0));
       //__lcd_newline();
       //printf("RA3: %.3x", readADC(3));
       
       //__delay_ms(400);
        
    
    /* Main loop. */
    
        


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
