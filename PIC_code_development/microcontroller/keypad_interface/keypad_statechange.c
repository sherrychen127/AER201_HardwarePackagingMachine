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
int state = 0;
char temp;
int assembly_step = 0;

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
    
    /* Main loop. */
    while(1){
        if (state == 0){
            
        
        printf("assembly step:");
        __lcd_home();
        __delay_ms(1000);
        //printf("CHOCOLATE?!");
        //__lcd_home();
        //__delay_ms(1000);
        }
        
        else if (state ==1){
            //initLCD();
            //__lcd_clear();
            printf("fastener set:");
            __lcd_home();
            //__delay_ms(1000);
        }
        
        else if (state == 2){
            //initLCD();
            
            printf("number:");
            __lcd_home();
            __delay_ms(1000);
        }
        
        
    }
    
    
    //void get_assembly_step();
        
    }

void get_assembly_step(){
    //if (temp == 'D'){
    //    step = 1;
    //}
    while (1){
        initLCD();
        printf("assembly_step");
        __lcd_home();
        __delay_ms(1000);
    
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
            temp = keys[keypress];
            
            //get assembly step
        if (state == 0){
        //store the value to variable assembly_step
            if(temp == '5'){
                assembly_step = 5;
            }
            else if (temp == '6') {
                assembly_step = 6;
            }
            else if (temp == '7'){
                assembly_step = 7;
            }
            else if (temp == '8'){
                assembly_step = 8;
                //state = 1;
            }
            else if (temp == 'D'){
                state = 1;
                initLCD();
            }
        }
        
        else if(state == 1){
            if (temp == 'D'){
                state = 2;
                initLCD();
            }
        }
            
        
        
          
        }
                
                   
        
        
        
        
        __lcd_home();
        
        INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
        //return;
    }



