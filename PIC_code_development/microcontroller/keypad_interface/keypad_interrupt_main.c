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

#include <string.h>

/***** Constants *****/
const char keys[] = "123A456B789C*0#D"; 
int fastener[100];
int state = 0;
char temp;
int assembly_step = 0;
int counter = 0; //useless
int counter_step = 0; //keep track of how many fastener_set + number displayed
int error = 0;//useless
int valid = 0;
int number = 0;

int prev_state;
int B=0,N=0,S=0,W=0;
const char strs[20][4] = {"B","N","S","W","BN","BS","BW","BBN","BBS","BBW","BNW",
                           "BSW","BWW","BNWW","BSWW","BBSW","BBNW","BNNW",
                            "BNNN","BWWW"};
char current_set[4];
char temp_set[4];
char final_set[8][4];



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
        
        if (state ==1){
            initLCD();
            //__lcd_clear();
            printf("fastener set:");
            //__lcd_home();
            __delay_ms(1000);
        }
        
        if (state == 2){
            initLCD();
            
            printf("number:");
            //__lcd_home();
            __delay_ms(1000);
        }
        
        if (state == 3){
            initLCD();
            printf("Done!");
            __delay_ms(2000);
            //display total instructions!!!!
        }
        
        //display error messages
        //if(state == 3){
        //    initLCD();
        //    if (error == 1){
        //        printf("ERROR!");
        //        __lcd_home();
        //        __delay_ms(2000);
        //        error = 0;
        //    }
        //    state = prev_state;
        //}
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
        
            //__lcd_newline();
            unsigned char keypress = (PORTB & 0xF0) >> 4;
            //putch(keys[keypress]);
            char temp = keys[keypress];
            
            //go back to previous state
            if(temp == 'A'){
                state = prev_state;
                INT1IF = 0; 
                return;
            }
            
            //get assembly step
            
        if (state == 0){
        //store the value to variable assembly_step
            
            if(temp == '5'){
                assembly_step = 5;
                prev_state = state;
                state = 1;
                __lcd_newline();
                putch(keys[keypress]);
                
            }
            else if (temp == '6') {
                assembly_step = 6;
                prev_state = state;
                state = 1;
                __lcd_newline();
                putch(keys[keypress]);
            }
            else if (temp == '7'){
                assembly_step = 7;
                prev_state = state;
                state = 1;
                __lcd_newline();
                putch(keys[keypress]);
                
            }
            else if (temp == '8'){
                assembly_step = 8;
                prev_state = state;
                state = 1;
                __lcd_newline();
                putch(keys[keypress]);
                
            }
            else{
                //initLCD(); 
                //error!!!
                //error = 1;
                //prev_state = state;
                //state = 3;
                initLCD();
                printf("ERROR!another number!");
                __delay_ms(1000);
                
            }
            //else if (temp == 'D'){
            //    state = 1;
            //}
            __delay_ms(2000);
            counter++;
            //__lcd_home();
            INT1IF = 0; 
                //return;
        }
        
            
            
        //state = 1: choose fastener_set
            
            
        if(state == 1){
            //error = 0;
            //if (counter == 0){
            //    __lcd_newline();
            //}
            
            
                if (temp == 'A'){
                    state = prev_state;
                }
            
                if (temp == '1'){
                     __lcd_newline();
                    putch('B');
                    strcpy(temp_set,"B");
                    strcat(current_set,temp_set);
                }
            
                if(temp == '2'){
                     __lcd_newline();
                    putch('N');
                    strcpy(temp_set,"N");
                    strcat(current_set,temp_set);
                }
            
                if(temp == '3'){
                    __lcd_newline();
                    putch('S');
                    
                    strcpy(temp_set,"S");
                    strcat(current_set,temp_set);
                }
                if (temp == '4'){
                     __lcd_newline();
                    putch('W');
                    
                    strcpy(temp_set,"W");
                    strcat(current_set,temp_set);
                    strcpy(temp_set,"");
                }
                
            
                else{
                    if (temp == '*'){
                        
                        
                        for (int i=0;i<20;i++){
                            if (!strcmp(current_set,strs[i])){
                                strcpy(final_set[counter_step],current_set);
                                strcpy(current_set,"");
                                strcpy(temp_set,"");
                                valid = 1;
                                state = 2;
                                __lcd_newline();
                                printf("right");
                                printf("%s",current_set);
                                __delay_ms(2000);
                                counter = 0;
                                
                            }
                            
                        }
                        if (valid != 1){

                            initLCD();
                            printf("wrong set!");
                            printf("%s",current_set);
                            strcpy(current_set,"");
                            __delay_ms(2000);
                            counter = 0;
                        }
                        
                        //initLCD();
                    }
                    //else if (temp!= '*'){
                    //    initLCD();
                    //    //printf("Error!");   //error message when press other buttons
                    //    __delay_ms(2000);
                    //}
                    //error = 1;
                    //prev_state = state;
                    //state = 3;
                }
            
            counter ++; 
            if (counter > 5){
                initLCD();
                printf("wrong!");
                strcpy(current_set,"");
                counter = 0;
            }
            INT1IF = 0; 
            return;
        }
            
            
            //state =2: choose number of fastener set
            
        if (state ==2){
            counter = 0;
            
                __lcd_newline();
                putch(keys[keypress]);
                //printf("la");
                __delay_ms(500);
                
                if (keys[keypress] == '2'){
                    state = 1;
                    //printf("ls");
                    counter_step++;
                }
                
                
                switch(temp){
                    case '1': 
                        number = 1;
                        break;
                    case '2':
                        number = 2;
                        break;
                    case '3':
                        number = 3;
                        break;
                    case '4':
                        number = 4;
                        break;
                    default:
                        initLCD();
                        printf("wrong number!");
                    
                }
                
                if (counter_step >3){
                    state = 3;
                }
                
                //if (counter_step == assembly_step){
                //    state = 3;
                //}
                //else{
                //    initLCD();
                //    printf("wrong again!");
                 //   __lcd_home();
                 //   __delay_ms(2000);
                //}
                
                
            
            
            
            
            INT1IF = 0; 
            return;
            
        }
                
                

        //__lcd_home();
        
        //INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
        //return;
    
}
}






