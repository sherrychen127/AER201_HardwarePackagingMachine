/*
 * File:   main.c
 * Author: Sherry Chen
 *
 * Created on March 15, 2018
 *

 */



#include <xc.h>
#include "configBits.h"
#include "lcd.h"
int count=0;


void interrupt ISR(){
    
    if (INTCONbits.TMR0IF){
        INTCONbits.TMR0IF = 0;
        count ++;
        //if (count >= 122){
            count = 0;
            initLCD();
            printf("yay");
            __delay_ms(300);
            //__lcd_home();
        //}
    }
}

void main(){
     // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    //OSCCON = 0xF2;  // Use 8 MHz internal oscillator block                      //oscillator initialize
       
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS1 = 1;
    OSCTUNEbits.PLLEN = 1;
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
    /*
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    TRISD = 0x00;
    PORTD = 0x00;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 1;  //clear timer overflow
    ei();  
    
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 0;
    
    T0CONbits.T0PS0 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 1;
    
    TMR0H = 0xB;
    TMR0L = 0xDC;
    T0CONbits.TMR0ON = 1;
    
    */
    ei();
    initLCD();
    //printf("start");
    __delay_ms(200);
    
    
    //counter == 106
    
    //
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 1;  //8 bit
    T0CONbits.PSA = 0;  //assign timer0 prescaler
    T0CONbits.T0CS = 0;  //clock source select   //1
    T0CONbits.T0PS0 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 1;
 
    //PSA = 0;
    //T0CS = 0;
    //T08BIT = 0;
    //TMR0IE = 0;
    
}
