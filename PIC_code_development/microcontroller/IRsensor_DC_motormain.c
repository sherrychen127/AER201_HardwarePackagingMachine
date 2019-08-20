/*
 * File:   main.c
 * Author: sherrychan
 *
 * Created on February 20, 2018, 11:32 AM
 */
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
//#include "keypad.h"
#include <string.h>

//int mode = 0;

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
        TRISAbits.RA1 = 1; //RA0
        unsigned char input = PORTAbits.RA1;
        //printf("input:");
        putch(array[input]);
        __delay_ms(500);
        __lcd_home();
        
        if (array[input] == '1'){
            LATCbits.LATC2 = 1;  //RB0 HIGH
            TRISCbits.RC2 = 0;
            __delay_ms(100);
        }
        LATCbits.LATC2 = 0;  //RB0 HIGH
        TRISCbits.RC2 = 0;
        __delay_ms(100);
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
            if(temp == '4'){
                assembly_step = 4;
                prev_state = state;
                state = 1;
                __lcd_newline();
                putch(keys[keypress]);
                
            }
            else if(temp == '5'){
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
                printf("Wrong number! ");
                __delay_ms(1000);
                
            }
            //else if (temp == 'D'){
            //    state = 1;
            //}
            __delay_ms(2000);
            //counter++;
            //__lcd_home();
            INT1IF = 0; 
            return;
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
                    counter++;
                }
            
                if(temp == '2'){
                     __lcd_newline();
                    putch('N');
                    strcpy(temp_set,"N");
                    strcat(current_set,temp_set);
                    counter++;
                }
            
                if(temp == '3'){
                    __lcd_newline();
                    putch('S');
                    
                    strcpy(temp_set,"S");
                    strcat(current_set,temp_set);
                    counter++;
                }
                if (temp == '4'){
                     __lcd_newline();
                    putch('W');
                    
                    strcpy(temp_set,"W");
                    strcat(current_set,temp_set);
                    //strcpy(temp_set,"");
                    counter++;
                }
                
            
                else{
                    if (keys[keypress] == '*'){
                        
                        
                        for (int i=0;i<20;i++){
                            if (strncmp(current_set,strs[i],5) == 0){
                                strcpy(final_set[counter_step],current_set);
                                strcpy(current_set2,current_set);
                                //strcpy(current_set,"");
                                //strcpy(temp_set,"");
                                valid = 1;
                                state = 2;
                                //__lcd_newline();
                                initLCD();
                                printf("correct!");
                                __delay_ms(1000);
                                //__lcd_newline();
                                printf("%s",current_set);
                                
                                strcpy(current_set,"");
                                __delay_ms(2000);
                                counter = 0;
                                break;
                                
                            }
                            else if (i == 19){
                                break;
                            }
                            
                        }
                        if (valid != 1){

                            initLCD();
                            printf("wrong set!");
                            printf("%s",current_set);
                            strcpy(current_set,"");
                            __delay_ms(2000);
                            counter = 0;
                            valid = 0;
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
            
            //counter ++; 
            if (counter > 4){
                initLCD();
                printf("wrong!");
                //printf(counter);
                __delay_ms(1000);
                //strcpy(current_set2,current_set);
                strcpy(current_set,"");
                
                //strcpy(current_set2,"");
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
                
                if (keys[keypress] == '1'||keys[keypress] == '2'|| keys[keypress] == '3' ||keys[keypress] == '4'){
                    //state = 1;
                    switch(keys[keypress]){
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
                    case '5':
                        number = 5;  
                        break;
                    default:
                        initLCD();
                        printf("Wrong input");     
                        __delay_ms(1000);
                }
                
                
                is_valid();
                
                if ( check() == 0){
                    initLCD();
                    __lcd_home();
                    printf("TOO MANY");
                    
                    __delay_ms(1000);
                    state = 2;
                    number = 0;
                }
                
                
                else if (counter_step >= assembly_step-1){
                    final_number[counter_step] = number;
                    state = 3;
                }
                else if ( check() == 1){
                    state = 1;
                    initLCD();
                    printf("okay!");
                    __delay_ms(1000);
                    final_number[counter_step] = number;
                    counter_step++;
                }
                    
                        
                }
                    
                }
                
        
                
                
            
            
            B=0;N=0;S=0;W=0;
            total_number = 0;
            
            INT1IF = 0; 
            return;
            
        }
                
                

        //__lcd_home();
        
        //INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
        //return;
    
}