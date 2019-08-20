/*
 * File:   main.c
 * Author: sherrychan
 *
 * Created on February 20, 2018, 11:32 AM
 */
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "DCmotor.h"
#include "keypad.h"


int mode = 0;   //overall modes of operation of the machine
//int white_tape = 0;

//int max = 5;
int change_mode = 0;   //variable that change mode=0 to mode=1

int motor_counter=0;

int operation = 0;
int operation_time = 0; //variable for interrupt

int counter_test = 0; //useless(testing purposes))


unsigned char time[7]; 
//#include "keypad.h"






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
    
    //RTC_setTime();                                                              // comment for later runs
    //while(1) {
    //    __lcd_clear();
    //    __lcd_home();
        
       /* Print results to character LCD. Since ADC results are 10 bits, they
        * are split up into two registers ADRESH and ADRESL. The results of the
        * ADC are displayed in hexadecimal so that the values in each of these
        * registers will be easily visible; ADRESL corresponds to the two least
        * significant digits, while ADRESH corresponds to the most significant 
        * bit. */
    //   printf("RA2: %.3x", readADC(2));
    //   __delay_ms(100); 
    //   __lcd_newline();
    //   if (readADC(2)<26500){
    //       counter_test++;
    //       printf("%d",counter_test);
    //       __delay_ms(100);
    //       __lcd_home();
    //       
    //   }
    //}
    
    while(1){
    //    if (mode == 0){
    //        //operation = 1;
    //        printf("1:date and time");
    //        __lcd_newline();
    //        printf("2:instruction");
    //        __delay_ms(300);
    //        __lcd_home();
    //       while(1){
    //             
    //            if (change_mode == 1){
    //                mode = 1;
    //            //    operation = 0;
    //                break;
    //            }
    //        }
    //    }
        
        if (mode == 0){
            /* Main loop. */
            initLCD();
            while(1){
                if (state == 0){
                    //motorStart_0();
                    __lcd_home();
                    printf("assembly step:");
                    __delay_ms(1000);
                    __lcd_newline();
                    }
                if (state ==1){
                    initLCD();
                    printf("fastener set:");
                    __lcd_newline();
                    printf("%s",current_set);
                    __delay_ms(500);
                }
        
                if (state == 2){
                    initLCD();
                    printf("number:");
                    __delay_ms(500);
                }
        
                if (state == 3){
                    initLCD();
                    printf("Done!");
                    __delay_ms(2000);
                    initLCD();
                    printf("assembly step:%d",assembly_step);
                    __delay_ms(1000);
                    for ( i=0; i<assembly_step; i++){
                        //__lcd_newline();
                        initLCD();
                        //printf("assembly step:%d",assembly_step);
                        printf("step");
                        printf("%d", i);
                        printf(":");
                        printf("%s", final_set[i]);
                        printf(",");
                        printf("%d",final_number[i]);
                        __delay_ms(1000);
                        __lcd_newline();
                        //printf(final_number[i]);
                
                        //mode = 1;
                        __delay_ms(1000);
                    
                    }
                    for (i = 0; i<8; i++){
                        initLCD();
                        printf("%d",compartment_array[i]);
                        printf(" B:");
                        printf("%d",B_array[i]);
                        printf(" N:");
                        printf("%d",N_array[i]);
                        printf(" S");
                        printf("%d",S_array[i]);
                        printf(" W:");
                        printf("%d",W_array[i]);
                        __delay_ms(1000);
                        __lcd_newline();
                    
                    }
                    mode = 2;
                    break;
             
                }
      
            }
        }
    
    /*******************mode = 1 *********************
     * Servo_motor rotate
     * interface contact sensor
     * if contact sensor = 1
     * polling for IR sensor
     * if IR sensor = 1 -> motor stop
     * 
     
     
     **************************************************/
    
        if (mode == 1){
            //servoRotate90();
            initLCD();
        
            if (white_tape == 0){
                initLCD();
                while(1){
                    printf("%d",read_IR());
                    __delay_ms(100);
                    __lcd_home();
                    if (read_IR() == 1){
                        white_tape = 1;
                        break;
                    }
                    
                
                }
            }
        
        
            else if (white_tape == 1){
                putch('1');
                __delay_ms(200);
                
                //servoRotate0();
                __delay_ms(200);
                    //stop servo
                    initLCD();    
                    //generate_compartment_array(4);                              // comment
                    
                    for (i = 0; i<8; i++){
                        
                        if (compartment_array[i]==1){                            //change to 1
                            //servoRotate90();
                            //__delay_ms(300); 
                            //servoRotate0();
                            //__delay_ms(200);
                            
                            /*test*/
                            //initLCD();
                            
                            /*end test*/
                            
                            initLCD();
                            
                            
                            initLCD();
                            printf("C");
                            printf("%d",i);
                            printf(":");
                            __delay_ms(800);
                            initLCD();
                            while(1){
                                __lcd_home();
                                if (B_count>= B_array[i]&&S_count>= S_array[i]&&N_count>= N_array[i]&&W_count>= W_array[i]){
                                    printf("B:%d S:%d N:%d W:%d",B_count,S_count,N_count,W_count);
                                    __delay_ms(1000);
                                    B_count = 0;
                                    S_count = 0;
                                    N_count = 0;
                                    W_count = 0;
                            
                                    //__delay_ms(1000);
                                    break;
                                }
                                
                                
                                if (B_count< B_array[i]){
                                    
                                    printf("B:");
                                    printf("%d", B_count);    
                                    __delay_ms(800);
                                    //__lcd_home();
                                    
                                    B_count++;
                                }
                                if (S_count< S_array[i]){
                                    printf("S:");
                                    printf("%d", S_count);    
                                    __delay_ms(800);
                                    S_count++;
                                }
                                
                                if (N_count< N_array[i]){
                                    printf("N:");
                                    printf("%d", N_count);    
                                    __delay_ms(800);
                                    N_count++;
                                }
                                
                                if (W_count< W_array[i]){
                                    printf("W:");
                                    printf("%d", W_count);    
                                    __delay_ms(800);
                                    W_count++;
                                }
                                
                                
                                
                                
                            }
                            //while(B_count< B_array[i]){                             // change max to B_array[i];
                            //    //motorStart_0();
                                
                            //    //if (readADC(2)<250){                                  //uncomment
                            //    initLCD();
                            //        //__delay_ms(2000);
                            //        printf("B:");
                            //        printf("%d", B_count);    
                            //        __delay_ms(800);
                            //        __lcd_home();
                            //        B_count ++;
                            //    
                                //}                                              //uncomment
                                
                            //}
                            
                            //while(S_count < S_array[i] ){                             // change max to B_array[i];
                            //    //motorStart_0();                                  // change 0 to 1;
                            //    if (260>250){                                    //if (readADC(0000)>250)
                            //        printf("S:");
                            //        printf("%d", S_count);    
                            //        __delay_ms(800);
                            //        __lcd_home();
                            //        S_count ++;
                            //   
                            //    }
                            //    
                            //}
                            
                            //while(N_count < N_array[i] ){                             // change max to B_array[i];
                            //    //motorStart_0();                                  // change 0 to 2;
                            //    if (260>250){
                            //        printf("N:");
                            //        printf("%d", N_count);    
                            //        __delay_ms(800);
                            //        __lcd_home();
                            //        N_count ++;
                            //    
                            //    }
                            //    
                            //}
                            
                            //while(W_count < W_array[i] ){                             // change max to B_array[i];
                            //    //motorStart_0();                                  // change 0 to 3;
                            //    if (260>250){
                            //        printf("W:");
                            //        printf("%d", W_count);    
                            //        __delay_ms(800);
                            //        __lcd_home();
                            //        W_count ++;
                                
                            //    }
                            //}
                            //motorStop_0();
                            
                            
                            
                            
                        }
                        else{
                            //motorStop_0();
                            
                            //servoRotate90();
                            //__delay_ms(1000); 
                            //servoRotate0();
                            //__delay_ms(1000);
                            
                            /*test*/
                            initLCD();
                            printf("C");
                            printf("%d",i);
                            printf(":");
                            printf("done");
                            __delay_ms(3000);
                            /*end test*/
                            
                        }
                    }
                    
                    
                
                                
            }
            // mode = 3;
            store_prev();
            mode = 3;
        }
        
    
    
    /************************
     * mode = 3
     
     *************************/
    
        if (mode == 3){
            initLCD();
            //for (i = 0; i<8; i++){
            //    printf("C%d",i);
            //    printf(":");
            //
            //    printf("set:");
            //    printf(prev_set[i]);
            //    printf(",");
            //    printf("%d",prev_number[i]);
            //    __delay_ms(1000);
            //    __lcd_home();
            //}
            //initialize();
            //mode = 1;
            
            servoRotate0();
            __delay_ms(200);
            
            servoRotate180();
            __delay_ms(300);
            while(motor_counter<40){
                motorStart_0();
            //__delay
                motor_counter++;
                B_count ++;
                
            }
            motorStop_0();
            
            printf("remain:%d",B_count);
            __delay_ms(3000);
            __lcd_home();
            initLCD();
            printf("you're done");
            __delay_ms(1000);
            __lcd_home();
            while(1){
                operation = 1;
                printf("1: operation time");
                __delay_ms(1000);
                __lcd_home();
                
                if(operation_time == 1){
                    break;
                }
            }
            initialize();
            mode = 0;
            
        }
    //if (mode == 3){
    //    initLCD();
    //    while(1){
    //        //servoRotate0();
    //        motorStart_0();
    //        
    //        printf("yay");
    //        __delay_ms(500);
    //        __lcd_home();
    //        
    //        for (i = 0; i<8; i++){
    //            if (compartment_array[i] == 1){
    //                initLCD();
    //                printf("1");
    //                __delay_ms(200);
    //                __lcd_home();
    //            }
    //            else{
    //                initLCD();
    //                printf("0");
    //                __delay_ms(200);
    //                __lcd_home();
    //            }
    //        }
    //    }
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
            
            //
        
        if(operation == 1){
            if (temp == '1'){
                
                
                
                operation_time = 1;
                INT1IF = 0; 
                return;
            }
            
        }
        
        //if (mode == 0){
        //    if (temp == '2'){
        //        initLCD();
        //        putch(temp);
        //        __delay_ms(100);
        //        mode = 1;
        //        change_mode = 1;
                
                
        //    }
        //    else if (temp == '1'){
        //        
        //        //while(1){
        //        /* Reset RTC memory pointer. */
        //        putch(temp);
        //        __delay_ms(300);
        //        display_RTC();
        //    }
        //    INT1IF = 0; 
        //    return;
        //}
        
        //else{   
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
            
            
                generate_compartment_array(assembly_step);//generate compartment array
            
                //__delay_ms(2000);
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
                
                if (keys[keypress] == '*'){
                    //initLCD();
                    //printf("hs");
                    __delay_ms(1000);
                    counter ++;
                        for (int i=0;i<20;i++){
                            if (strncmp(current_set,strs[i],4) == 0){
                                strcpy(final_set[counter_step],current_set);
                                strcpy(current_set2,current_set);
                                //strcpy(current_set,"");
                                //strcpy(temp_set,"");
                                valid = 1;
                                state = 2;
                                //__lcd_newline();
                                initLCD();
                                printf("correct!");
                                __delay_ms(500);
                                //__lcd_newline();
                                printf("%s",current_set);
                                
                                strcpy(current_set,"");
                                __delay_ms(1000);
                                counter = 0;
                                break;
                                
                            }
                    }
                    if (valid != 1){
                            
                            initLCD();
                            printf("wrong set!");
                            printf("%s",current_set);
                            strcpy(current_set,"");
                            __delay_ms(1000);
                            counter = 0;
                            valid = 0;
                        }
                    valid = 0;
                
                }
            
             
            if (counter >= 5){
                
                initLCD();
                printf("wrong!");
                //printf(counter);
                __delay_ms(500);
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
                    
                    __delay_ms(500);
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
        //}
        }
                
                

        //__lcd_home();
        
        //INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
        //return;

}




void initialize(){
    white_tape = 0;
    mode = 0;
    state = 0;
    assembly_step = 0;
    counter_step = 0;
    
    valid = 0;
    number = 0;
    total_number=0;
    
    B=0,N=0,S=0,W=0;
    
    B_count= 0;   //keep track of the dispensed fasteners;
    S_count= 0;
    N_count= 0;
    W_count= 0;
    
    for (i=0;i<8;i++){
        compartment_array[i] = 0;
        compartment_number[i] = 0;
        B_array[i] = 0;
        N_array[i] = 0;
        S_array[i] = 0;
        W_array[i] = 0;
    }
    
    //compartment_array[8] = {0,0,0,0,0,0,0,0};   //which C is to be dispensed, index = compartment number 
    //compartment_number= {0,0,0,0,0,0,0,0}; //store the compartment number(index))

    //B_array[8] = {0,0,0,0,0,0,0,0};
    //S_array[8] = {0,0,0,0,0,0,0,0}; 
    //N_array[8]= {0,0,0,0,0,0,0,0};
    //W_array[8]= {0,0,0,0,0,0,0,0};


}


//PR sensor
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



