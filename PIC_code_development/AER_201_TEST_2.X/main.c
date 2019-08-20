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
        

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    OSCCON = 0xF2;  // Use 8 MHz internal oscillator block                      //oscillator initialize
    
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
                
                        //mode = 1;
                        __delay_ms(1000);
                    
                    }
                    //print summary
                    for (i = 0; i<8; i++){
                        initLCD();
                        printf("%d",compartment_array[i]);
                        printf(" B:");
                        printf("%d",B_array[i]);
                        printf(" N:");
                        printf("%d",N_array[i]);
                        printf(" S:");
                        printf("%d",S_array[i]);
                        printf(" W:");
                        printf("%d",W_array[i]);
                        __delay_ms(1000);
                        __lcd_newline();
                    
                    }
                    initLCD();
                    printf("start operation");
                    __delay_ms(700);
                    //__lcd_home
                    
                    
                    //operation time initial;
                    
                    
                    get_RTC_initial();
                    
                    
                    
                    
                    
                    mode = 2;                     //mode change
                    break;
             
                }
      
            }
        }
    
    /*******************mode = 2 *********************
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
            
            //initial ramp angle using i2C
            initRamp();
            
            //rotate 360+ degrees, to open the handle
            while(1){
                if (gear_counter>= 50){
                    gear_counter = 0;    //initialize the counter
                    break;
                }
                servoRotate_clockwise();
                count_gear();           //counter++, init_position remains the same
                printf("gear:%d",gear_counter);         
                //__delay_ms(50);
                __lcd_home();
            }
            
            //stop when white tape detected. manually measure the distance between white tape 
            while(1){
        
                servoRotate_clockwise();
                count_gear();           //counter++, init_position ++ when white_tape detected
                printf("gear:%d",gear_counter);         
                //__delay_ms(50);
                __lcd_home();
                if (read_IR() == 1){              
                    white_tape = 1;                //detect white_tape
            
                    servoRotate_ConStop();    //stop servo
                    break;
                }
            }
            servoRotate_ConStop();          //stop servo
            __delay_ms(200);
            gear_counter = 0;   //initialize counter
            compartment_pos = init_position/5 -1;     
            
            
        }
        
        
        //start dispensing each compartment
    
        i = 0;
        while (i<7){         //only need to rotate 7 times
            if (compartment_pos == 8){
                compartment_pos = 0;  //might not start from C0
            }
            if (compartment_array[compartment_pos] != 0){
                servoRotate_ConStop();           //start dispensing here
                __delay_ms(2000);
                
                initLCD();
                printf("%d",B_count);
                __delay_ms(50);
                motorStart_0();
                
                /***********dispense bolts**************************************/
                while (1){
       
                    if (B_count == B_array[compartment_pos]){       //max number
                        motorStop_0();
                        break;
                    }
                    __lcd_home();
       
                    //printf("RA0: %.3x", readADC(0));
                    if (readADC(0)<= 250 ){   //800      before caliberation: 32800
                        //motorStart_0();  
                        B_count ++;
                        initLCD();
                        printf("%d", B_count);
                        __delay_ms(10);
                    }
                    //__delay_ms(60);           //nuts = 70 ms
                }
                initLCD();
                printf("done");
                __delay_ms(500);
                /*******************************dispense Nuts****************************/
                /*********** 1:Nuts 
                 * motor_1: RC1
                 * readADC: RA1
                 *************/
 
    
                initLCD();
                printf("%d",N_count);
                __delay_ms(50);
                motorStart_1();
    
                while(1){
            
                    if (N_count == N_array[compartment_pos]){
                        motorStop_1();
                        break;
                    }
                    if (readADC(1)<=250 ){   //800
                        //motorStart_0();  
                        N_count ++;
                        initLCD();
                        printf("%d", N_count);
                        __delay_ms(3);
                    }
            
                }
    
                initLCD();
                printf("done");
                __delay_ms(500);
                
                
                
                /***********2: spacer*******************************************/
                /*********** 
                 * motor_2: RC2
                 * readADC : RA5
     
                 *************/
    
                initLCD();
                printf("%d",S_count);
                __delay_ms(50);
                motorStart_2();
    
                while(1){
            
                    if (S_count == S_array[compartment_pos]){
                        motorStop_2();
                        break;
                    }
                    if (readADC(5)<=250 ){   //800
                        //motorStart_0();  
                        S_count ++;
                        initLCD();
                        printf("%d", S_count);
                        __delay_ms(50);
                    }
            
                }
                
                initLCD();
                printf("done");
                __delay_ms(500);
            }
        
            
            
            /*********** 3: washer ********************************************
             * motor_3: RC5
             * readADC: RA4
             *************RC5*/
            initLCD();
            printf("%d",W_count);
            __delay_ms(50);
            motorStart_3();
    
            while(1){
            
                if (W_count == W_array[compartment_pos]){
                    motorStop_3();
                    break;
                }
                if (readADC(4)<=250 ){   //800
                    //motorStart_0();  
                    W_count ++;
                    initLCD();
                    printf("%d", W_count);
                    __delay_ms(50);
                }
            
            }
    
            initLCD();
            printf("done");
            __delay_ms(500);
    

            //done dispensing one compartment, rotate to the next one
            while(gear_counter<=5){ 
                servoRotate_clockwise();         //rotate one compartment
                count_gear();
                initLCD();
                printf("%d",gear_counter);
                __lcd_home();
                
            }
            //reset variables
            B_count = 0;
            N_count = 0;
            S_count = 0;
            W_count = 0;
            gear_counter = 0;
            
            //increment variables
            compartment_pos++;
            i++;
        }
        
        
        //rotate _ramp to dispense the remaining fasteners to the bottom reservoirs.
        ramp_Rotate();
        //dispensing the remain fasteners, and rotate counterclockwise 360+45 + to close the lid
        
        //start the motor
        motorStart_0();
        motorStart_1();
        motorStart_2();
        motorStart_3();

        while(1){
            
            if (gear_counter>=50){
                servoRotate_ConStop();
            }
            else{
                servoRotate_counter();     //rotate servo and close the lid
                count_gear();
            }
            
            //dispense remaining fasteners;
            //if spacingtime > threshold: reservoirs are empty
            if (B_done == 1 && S_done == 1 && N_done == 1 && W_done ==1){
                
                break;      //break!
            }
            if (B_spacingTime>= 15000){
                motorStop_0();    //stop the motor
                B_done = 1;
            }

            if (N_spacingTime>= 15000){
                motorStop_1();    //stop motor
                N_done = 1;
            }

            if (S_spacingTime>= 15000){
                motorStop_2();
                S_done = 1;
            }

            if (W_spacingTime>= 15000){
                motorStop_3();
                W_done = 1;
            }
            //detect the remaining fasteners

            if (readADC(0)<=250 ){   //800
                //motorStart_0();  
                B_spacingTime=0;
                B_remain ++;
            }
            initLCD();
            printf("B%d", B_remain);
            
            if (readADC(1)<=250 ){   //800
                //motorStart_0(); 
                N_spacingTime=0; 
                N_remain ++;
                
            }
            printf(",N%d", N_remain);
            if (readADC(5)<=250 ){   //800
                //motorStart_0(); 
                S_spacingTime=0; 
                S_remain ++;
                //initLCD();
                //__delay_ms(10);
            }
            printf(",S:%d", S_remain);
            
            if (readADC(4)<=250 ){   //800
                //motorStart_0();  
                W_spacingTime=0;
                W_remain ++;
                //initLCD();
                
                //__delay_ms(30);
            }
            printf(",W:%d", W_remain);
            
            //increment spacting Time
            B_spacingTime+=200;
            N_spacingTime+=200;
            S_spacingTime+=200;
            W_spacingTime+=200;
        }    
        
        
        //display remaining fasteners:
        initLCD();
        printf("operation ends");
        __delay_ms(300);
        __lcd_clear();
        __lcd_home();
        
        
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
                 print operation summary
                 
                 */
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
    
    B_count= 0;   //keep track of the dispensed fasteners;
    S_count= 0;
    N_count= 0;
    W_count= 0;
    
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