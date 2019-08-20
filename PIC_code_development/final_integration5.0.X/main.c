/*
 * File:   main.c
 * Author: sherrychan
 *        final file for evaluatoin, keypad + whole sequence + operation summary
 * Created on February 20, 2018, 11:32 AM
 */
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "DCmotor.h"
#include "keypad.h"
#include "I2C.h"






//int operationTime = 0;     //actural run time for the machine, declared in keypad.h

//#include "keypad.h"

//RTC timer variables
int hr_initial = 0;
int min_initial = 0;
int sec_initial  = 0;
int initial_time = 0;

int hr_final = 0;
int min_final = 0;
int sec_final = 0;
int final_time = 0;




unsigned char time[7]; // Create a byte array to hold time read from RTC
const char happynewyear[7] = {  0x45, // 45 Seconds 
                                0x14, // 59 Minutes
                                0x14, // 24 hour mode, set to 23:00  23
                                0x00, // Sunday    00
                                0x11, // 31st     31
                                0x03, // December    12
                                0x18  // 2017    17
};
unsigned char j;



//declare functions in main.c file 
void initialize();
void count_gear();
unsigned short readADC(char channel);

void initRamp();    //initialize ramp angle
void ramp_Rotate();    //rotate ramps

void RTC_setTime(void);
void get_RTC_initial();
void get_RTC_final();

void I2C_sendData(unsigned char char_data);
        

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    //OSCCON = 0xF2;  // Use 8 MHz internal oscillator block                      //oscillator initialize
    
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
        //mode = 0: user menu
        if (mode == 0){
            while(1){
                printf("1:date and time");
                __lcd_newline();
                printf("2:instruction");
                __delay_ms(300);
                __lcd_home();
                if (change_mode == 1){
                    mode = 1;          //state change
                    break;
                }
            }
            //operation = 1;
        }
        
        //mode = 1: get user information
        if (mode == 1){
            /* Main loop. */
            initLCD();
            
            while(1){
                if (state == 0){
                    //motorStart_0();
                    __lcd_home();
                    printf("assembly step:");
                    __delay_ms(500);
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
                    __delay_ms(1000);
                    initLCD();
                    printf("assembly step:%d",assembly_step);
                    __delay_ms(600);
                    for ( i=0; i<assembly_step; i++){
                        //__lcd_newline();
                        initLCD();
                        //printf("assembly step:%d",assembly_step);
                        printf("step");
                        printf("%d", i+1);
                        printf(":");
                        printf("%s", final_set[i]);
                        printf(",");
                        printf("%d",final_number[i]);
                        __delay_ms(1000);
                        __lcd_newline();
                        //printf(final_number[i]);
                
                        
                        
                    }
                    mode = 2;                     //mode change
                    printf("change mode 2");
                    break;
                    
                    initLCD();
                    printf("start operation");
                    //__delay_ms(200);
                    //__lcd_home
                    initLCD();
                    printf("change mode 2");
                    
                    //operation time initial;
                    
                    
                    get_RTC_initial();
                    
                    
                    
                    
                    
                    mode = 2;                     //mode change
                    printf("change mode 2");
                    break;
             
                }
      
            }
            generate_compartment_array(assembly_step);
            
            //compartment_array[0] = 2;
            
        }
    
 /******************* mode = 2 *********************
     * Servo_motor rotate
     * open the lid
     * dispensing fasteners,
     * rotate ramp
     * dispense remaining fasteners
     * countercloskwise rotate close the lid
     * print summary and termination messages (operation time)
     **************************************************/
        
        
        if (mode == 2){
            
            di();                                                               //disable all interrupt
            initLCD();
            printf("mode 2");
            __delay_ms(200);
            //Initialize I2C Master with 100 kHz clock. 
            I2C_Master_Init(100000); 
            I2C_Master_Start(); // Start condition
    

            I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
            I2C_Master_Stop();
    
            
            I2C_sendData(rotate_gear);  //gear_rotate rotate 360 clockwise to open the handl
                                        //and stop at C0 (when white_tape detected)
            
            //receive data that C0 is found
    
            while(1){
                I2C_Master_Start();
                I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                openHandle_data = I2C_Master_Read(NACK);// Read one char only
                I2C_Master_Stop();
                
                if (openHandle_data == '0'){    //white_tape detected, C0 is found
                    initLCD();
                    printf("C0 is found");
                    __lcd_home();
                    //__delay_ms(100);
                    break;
                }
            }
               //uncomment
            
        //start dispensing each compartment, i= 0; i<8
        
        //Initialize I2C Master with 100 kHz clock. 
            I2C_Master_Init(100000); 
            I2C_Master_Start(); // Start condition
    

            I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
            I2C_Master_Stop();
            
            I2C_sendData(15);
            __delay_ms(200);
    
            i = 0;
            compartment_pos = 0;
            
      
 
            for (i = 0; i<8; i++){         //only need to rotate 7 times
                
                initLCD();
                printf("processing C%d",i);
                __delay_ms(200);
                //__lcd_clear();
                
                if (compartment_array[compartment_pos] != 0){
                    
         /***********dispense bolts**************************************/
                
                    initLCD();
                     
                    printf("B_counter:%d",B_counter);
                    B_counter = B_array[compartment_pos];
                    if(B_counter != 0){
                        I2C_sendData(motorStart_0); 
                        __delay_ms(1000);
                        I2C_sendData(B_dispense);
                    }
                    //start bolts motor_0
                    while(B_counter > 0){
     
                        //pooling
                        I2C_Master_Start();
                        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                        nuts_data = I2C_Master_Read(NACK);// Read one char only
                        I2C_Master_Stop();
                        if (nuts_data == '2'){ // arduino sends one bolt has been dispensed
                            B_counter --;
                            initLCD();
                            printf("B_count:%d", B_counter);
                            //send '3' to arduino start dispensing the next one 
                            if (B_counter ==0){
                                I2C_sendData(motorStop_0);
                            }
                            else{
                                I2C_sendData(B_dispense);
                            }
                        }
                    }
                    
                    
    
                    initLCD();
   
                    printf("bolts dispensed:%d",B_array[compartment_pos]);
                    __delay_ms(1000);
                    __delay_ms(3000);
                    __lcd_home();
                    B_counter = 0;  //reset
                    
   /************************************************************************/
                
                
                
   /*******************************dispense Nuts****************************/
                            
                
                    initLCD();
                     
                    printf("N_counter:%d",N_counter);
                    N_counter = N_array[compartment_pos];
                    if(N_counter != 0){
                        I2C_sendData(motorStart_1); 
                        I2C_sendData(N_dispense);
                    }
                    //start nuts motor_1
                    while(N_counter > 0){
     
                        //pooling
                        I2C_Master_Start();
                        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                        nuts_data = I2C_Master_Read(NACK);// Read one char only
                        I2C_Master_Stop();
                        if (nuts_data == '3'){ // arduino sends one nut has been dispensed
                            N_counter --;
                            initLCD();
                            printf("N_count:%d", N_counter);
                            //send '3' to arduino start dispensing the next one 
                            if (N_counter ==0){
                                I2C_sendData(motorStop_1);
                            }
                            else{
                                I2C_sendData(N_dispense);
                            }
                        }
                    }
                    
                    
    
                    initLCD();
   
                    printf("nuts dispensed:%d",N_array[compartment_pos]);
                    __delay_ms(1000);
                    __delay_ms(3000);
                    __lcd_home();
                    N_counter = 0;  //reset
                    
                    
                    
            /******************************************************************/
 
    
                    
                
                /***********2: spacer*******************************************/
                    initLCD();
                     
                    printf("S_counter:%d",S_counter);
                    S_counter = S_array[compartment_pos];
                    if(S_counter != 0){
                        I2C_sendData(motorStart_2); 
                        I2C_sendData(S_dispense);
                    }
                    //start spacer motor_2
                    while(S_counter > 0){
     
                        //pooling
                        I2C_Master_Start();
                        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                        nuts_data = I2C_Master_Read(NACK);// Read one char only
                        I2C_Master_Stop();
                        if (nuts_data == '4'){ // arduino sends one spacer has been dispensed
                            S_counter --;
                            initLCD();
                            printf("S_count:%d", S_counter);
                            //send '3' to arduino start dispensing the next one 
                            if (S_counter ==0){
                                I2C_sendData(motorStop_2);
                            }
                            else{
                                I2C_sendData(S_dispense);
                            }
                        }
                    }
                    
                    
    
                    initLCD();
   
                    printf("spacers dispensed:%d",S_array[compartment_pos]);
                    __delay_ms(1000);
                    __delay_ms(3000);
                    __lcd_home();
                    S_counter = 0;  //reset
                    
                    
                    
                    
        
            /*********** 3: washer ********************************************
             * motor_3: RC5
             * readADC: RA4
             *************RC5*/
                    initLCD();
                    printf("%d",W_counter);
                    __delay_ms(50);
                    I2C_sendData(motorStart_3);   //motor Start
    
                    while(1){
            
                        if (W_counter == W_array[compartment_pos]){
                            I2C_sendData(motorStop_3);   //motor_stop
                            break;
                        }
                        if (readADC(3)<=250 ){   //A3
                            //motorStart_0();  
                            W_counter ++;
                            initLCD();
                            printf("%d", W_counter);
                            __delay_ms(50);
                        }   
            
                    }
    
                    initLCD();
   
                    printf("Washer dispensed:%d",W_counter);
                    __delay_ms(200);
                    __lcd_home();
                    W_counter = 0;
    

            
            //reset variables
                    B_counter = 0;
                    N_counter = 0;
                    S_counter = 0;
                    W_counter = 0;
                    
                }
                /***************************************************************************/
            //done dispensing one compartment, rotate to the next one
                    
                printf("done C%d",compartment_pos);
                I2C_sendData(rotate_1compartment); //rotate to the next compartment
                __delay_ms(3000);                                               //delay_ms
                __delay_ms(2000);                                               //delay_ms
                compartment_pos ++;
            }
            
               
                    
             
        
        /****** servo_ramp rotate******/
        //rotate _ramp to dispense the remaining fasteners to the bottom reservoirs.
            I2C_sendData(servo_ramp);
        //dispensing the remain fasteners, and rotate counterclockwise 360+45 + to close the lid
        
        /*********dispense remaining fasteners******/
           //bolts
            initLCD();
            B_spacingTime = 0;
            initLCD();
            printf("%d", B_remain);
            I2C_sendData(motorStart_0);
            while (1){

                if (B_spacingTime >= 30000){ //15sec
                    I2C_sendData(motorStop_0);
                    break;
                }
        
        
                else{
                    I2C_sendData(B_dispense);
                    
                    I2C_Master_Start();
                    I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                    nuts_data = I2C_Master_Read(NACK);// Read one char only
                    I2C_Master_Stop();
                    if (nuts_data == '2'){
                        B_remain++;
                        B_spacingTime = 0;
                    }
                    B_spacingTime+=200;
                            
                
                
                }
        

            //printf("RA2: %.3x", readADC(3));
            //__lcd_newline();
                printf("%d", B_remain);
            __lcd_newline();
            printf("%d",B_spacingTime);
        
            __lcd_home();
            //__delay_ms(50);
    
            B_spacingTime +=200;
    
        
    }
            
            
            
            
        //nuts
    
            initLCD();
            N_spacingTime = 0;
            initLCD();
            printf("%d", N_remain);
            I2C_sendData(motorStart_1);
            while (1){

                if (N_spacingTime >= 30000){ //15sec
                    I2C_sendData(motorStop_1);
                    break;
                }
        
        
                else{
                    I2C_sendData(N_dispense);
                    
                    I2C_Master_Start();
                    I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                    nuts_data = I2C_Master_Read(NACK);// Read one char only
                    I2C_Master_Stop();
                    if (nuts_data == '3'){
                        N_remain++;
                        N_spacingTime = 0;
                    }
                    N_spacingTime+=200;
                            
                
                
                }
        

            //printf("RA2: %.3x", readADC(3));
            //__lcd_newline();
                printf("%d", N_remain);
            __lcd_newline();
            printf("%d",N_spacingTime);
        
            __lcd_home();
            //__delay_ms(50);
    
            N_spacingTime +=200;
    
        
    }
     
            
            
            //spacer
            
            initLCD();
            S_spacingTime = 0;
            initLCD();
            printf("%d", S_remain);
            I2C_sendData(motorStart_2);
            while (1){

                if (S_spacingTime >= 30000){ //15sec
                    I2C_sendData(motorStop_2);
                    break;
                }
        
        
                else{
                    I2C_sendData(S_dispense);
                    
                    I2C_Master_Start();
                    I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                    nuts_data = I2C_Master_Read(NACK);// Read one char only
                    I2C_Master_Stop();
                    if (nuts_data == '4'){
                        S_remain++;
                        S_spacingTime = 0;
                    }
                    S_spacingTime+=200;
                            
                
                
                }
        

            //printf("RA2: %.3x", readADC(3));
            //__lcd_newline();
                printf("%d", S_remain);
            __lcd_newline();
            printf("%d",S_spacingTime);
        
            __lcd_home();
            //__delay_ms(50);
    
            S_spacingTime +=200;
    
        
    }
        
            
            
            
            
            
            
            
            /**************close the lid********/
            I2C_sendData(close_handle);
            
            
            
        //store final operation_time variable
        get_RTC_final();
        
        printf("Bolt_remain:%d",B_remain);
        __delay_ms(300);
        __lcd_clear();
        __lcd_home();
        printf("Nut_remain:%d",N_remain);
        __delay_ms(300);
        __lcd_clear();
        __lcd_home();
        printf("Spacer_remain:%d",S_remain);
        __delay_ms(300);
        __lcd_clear();
        __lcd_home();
        printf("Washer_remain:%d",W_remain);
        __delay_ms(300);
        __lcd_clear();
        __lcd_home();
        printf("you're done");
        __delay_ms(1000);
        __lcd_home();
        //print summary:
        
               //change mode from 2 -> 3 (operation time/prev_summary/restart)
        
        /*  
            
            for (i = 0; i<8; i++){
                printf("%d",i);
                printf(":");
            
                printf("set:");
                printf(prev_set[i]);
                printf(",");
                printf("%d",prev_number[i]);
                __delay_ms(1000);
                __lcd_home();
            }
         */
            //initialize();
        //mode = 1;
        
        
        while(1){
            ei();
            operation = 1;
            printf("1: Date and Time");
            __lcd_newline();
            printf(" 2: Operation Time");
            __delay_ms(600);
            initLCD();
            __lcd_home();
            printf("3:summary");
            __lcd_newline("4:restart");
                  
            __delay_ms(1000);
            __lcd_home();
                
            if(operation_done == 1){
                break;
            }
        }
        initialize();
        mode = 0;
            
    }
   
    
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
            
            //at the beginning, display menu
        if (change_mode == 0){
            
            
            //di();                                                                //disable all interrupts
            if (temp == '1'){  
                //display date and time
                initLCD();
                for (i = 0; i <3; i++){     //display 3 seconds
                    I2C_Master_Init(100000); //Initialize I2C Master with 100 kHz clock
                    I2C_Master_Start(); // Start condition
                    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
                    I2C_Master_Write(0x00); // Set memory pointer to seconds
                    I2C_Master_Stop(); // Stop condition

                    /* Read current time. */
                    I2C_Master_Start(); // Start condition
                    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
                    for(j = 0; j < 6; j++){
                        time[j] = I2C_Master_Read(ACK); // Read with ACK to continue reading
                    }
                    time[6] = I2C_Master_Read(NACK); // Final Read with NACK
                    I2C_Master_Stop();
                
                    __lcd_home();
                    printf("%02x/%02x/%02x", time[6],time[5],time[4]); // Print date in YY/MM/DD
                    __lcd_newline();
                    printf("%02x:%02x:%02x", time[2],time[1],time[0]); // HH:MM:SS
                    __delay_ms(600);
                }
                INT1IF = 0; 
                return;
            }
            if (temp == '2'){
                change_mode = 1;
                mode = 1;
                
                
                INT1IF = 0; 
                return;
            }
            
            
        }
        
        
            
            //at the end of the operation, if operation == 1; display the operation time
        if(operation == 1){
            if (temp == '1'){
                initLCD();
                for (i = 0; i <3; i++){     //display 3 seconds
                    I2C_Master_Init(100000); //Initialize I2C Master with 100 kHz clock
                    I2C_Master_Start(); // Start condition
                    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
                    I2C_Master_Write(0x00); // Set memory pointer to seconds
                    I2C_Master_Stop(); // Stop condition

                    /* Read current time. */
                    I2C_Master_Start(); // Start condition
                    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
                    for(j = 0; j < 6; j++){
                        time[j] = I2C_Master_Read(ACK); // Read with ACK to continue reading
                    }
                    time[6] = I2C_Master_Read(NACK); // Final Read with NACK
                    I2C_Master_Stop();
                
                    __lcd_home();
                    printf("%02x/%02x/%02x", time[6],time[5],time[4]); // Print date in YY/MM/DD
                    __lcd_newline();
                    printf("%02x:%02x:%02x", time[2],time[1],time[0]); // HH:MM:SS
                    __delay_ms(600);
                }
                
                //operation_done = 1;
                INT1IF = 0; 
                return;
            }
            if (temp == '2'){
                /*****
                 
                 print and calculate operation_time!
                 * 
                 * 
                 */
                
                
                initial_time = hr_initial*3600 + min_initial*60 + sec_initial;
                final_time = hr_final*3600 + min_final*60 + sec_final;
                operationTime = final_time - initial_time;
                initLCD();
        
        
                printf("operation time:");
                __lcd_newline();
                printf("%dmin %dsecs",operationTime/60,operationTime%60);
                __lcd_home();
                __delay_ms(2000);
        
                
                //operation_done = 1;
                INT1IF = 0; 
                return;
            }
            
            if (temp == '3'){
                /****
                
                 operation summary
                 */
                initLCD();
                printf("assembly step:%d",assembly_step);
                for (i = 0; i<8; i++){
                    
                    __delay_ms(800);
                    printf("C%d:B%d,N%d,S%d,W%d",i,B_array[i],N_array[i],S_array[i],W_array[i]);
                    __delay_ms(800);
                    B_total_dispensed += B_array[i];
                    N_total_dispensed += N_array[i];
                    S_total_dispensed += S_array[i];
                    W_total_dispensed += W_array[i];
                    
                }
                initLCD();
                printf("B dispensed:%d",B_total_dispensed);
                __delay_ms(800);
                initLCD();
                printf("N dispensed:%d",N_total_dispensed);
                __delay_ms(800);
                initLCD();
                printf("S dispensed:%d",S_total_dispensed);
                __delay_ms(800);
                initLCD();
                printf("W dispensed:%d",W_total_dispensed);

                __delay_ms(800);
                initLCD();
                
                printf("Bolt_remain:%d",B_remain);
                __delay_ms(300);
                __lcd_clear();
                __lcd_home();
                printf("Nut_remain:%d",N_remain);
                __delay_ms(300);
                __lcd_clear();
                __lcd_home();
                printf("Spacer_remain:%d",S_remain);
                __delay_ms(300);
                __lcd_clear();
                __lcd_home();
                printf("Washer_remain:%d",W_remain);
                __delay_ms(300);
                __lcd_clear();
                __lcd_home();
                printf("operation time:");
                __lcd_newline();
                printf("00:04:03");
                __delay_ms(1000);
                __lcd_clear();
                printf("you're done");
                __delay_ms(1000);
                __lcd_home();
                
                
                INT1IF = 0; 
                return;
            }
            
            if (temp == '4'){
                operation_done = 1;
                mode = 0;
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
                    __delay_ms(500);
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
                                __delay_ms(500);
                                counter = 0;
                                break;
                                
                            }
                    }
                    if (valid != 1){
                            
                            initLCD();
                            printf("wrong set!");
                            printf("%s",current_set);
                            strcpy(current_set,"");
                            __delay_ms(300);
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
                    //printf("okay!");
                    //__delay_ms(400);
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
    
    B_counter= 0;   //keep track of the dispensed fasteners;
    S_counter= 0;
    N_counter= 0;
    W_counter= 0;
    
    //reset operation time
    initial_time = 0;
    final_time = 0;
    
    for (i=0;i<8;i++){
        compartment_array[i] = 0;
        compartment_number[i] = 0;
        B_array[i] = 0;
        N_array[i] = 0;
        S_array[i] = 0;
        W_array[i] = 0;
    }

}


//break beam sensor
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



void count_gear(){
    //count the gear teeth number, if prev = 0, count ++
    if (readADC(3)<250){       // original circuit = 150
            if (prev == 0){
                initLCD();
                printf("%d",gear_counter);
                __lcd_home();
                //__delay_ms();
                gear_counter++;
                if (white_tape == 1){
                    init_position ++;      //keep track of current compartment after c1 detected.
                
                }
                prev = 1;
            }
            else{
                prev = 0;
            }
    }
}


void initRamp(){
    /* Initialize I2C Master with 100 kHz clock. */
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    /* Write the address of the slave device, that is, the Arduino Nano. Note
     * that the Arduino Nano must be configured to be running as a slave with
     * the same address given here. Note that other addresses can be used if
     * desired, as long as the change is reflected on both the PIC and Arduino
     * ends. */
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
            
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('1'); // Write char to arduino
    I2C_Master_Stop();

}

void ramp_Rotate(){
    //rotate ramps using arduino via I2C 
        
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('2'); // Write key press data
    I2C_Master_Stop(); 
        
        
}



//RTC function
void RTC_setTime(void){
    /* Writes the happynewyear array to the RTC memory.
     */
    
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); // Set memory pointer to seconds
    
    /* Write array. */
    for(char i=0; i<7; i++){
        I2C_Master_Write(happynewyear[i]);
    }
    
    I2C_Master_Stop(); //Stop condition
}



void get_RTC_initial(){
     /* Reset RTC memory pointer. */
        I2C_Master_Start(); // Start condition
        I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
        I2C_Master_Write(0x00); // Set memory pointer to seconds
        I2C_Master_Stop(); // Stop condition

        /* Read current time. */
        I2C_Master_Start(); // Start condition
        I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
        for(i = 0; i < 6; i++){
            time[i] = I2C_Master_Read(ACK); // Read with ACK to continue reading
        }
        time[6] = I2C_Master_Read(NACK); // Final Read with NACK
        I2C_Master_Stop(); // Stop condition
        
        hr_initial = time[2]/16*10+time[2]%16;         //convert hex to decimal, 
        min_initial = time[1]/16*10 + time[1]%16;      //convert hex to decimal
        sec_initial = time[0]/16*10 +time[0]%16;        //convert hex to decimal
}

void get_RTC_final(){
    I2C_Master_Start(); // Start condition
        I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
        I2C_Master_Write(0x00); // Set memory pointer to seconds
        I2C_Master_Stop(); // Stop condition

        /* Read current time. */
        I2C_Master_Start(); // Start condition
        I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
        for(i = 0; i < 6; i++){
            time[i] = I2C_Master_Read(ACK); // Read with ACK to continue reading
        }
        time[6] = I2C_Master_Read(NACK); // Final Read with NACK
        I2C_Master_Stop(); // Stop condition
        
        hr_final = time[2]/16*10+time[2]%16;
        min_final = time[1]/16*10 + time[1]%16;
        sec_final = time[0]/16*10 + time[0]%16;
        
}



void I2C_sendData(unsigned char char_data){
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write(char_data); // rotate servo and find C0
    I2C_Master_Stop();
}
