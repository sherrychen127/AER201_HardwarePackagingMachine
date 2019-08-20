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
#include "GLCD_PIC.h"
#include "SPI_PIC.h"



// ********** parameters ************
#define EndProgramTimerCount 21 //85 for 3 mins
#define CloseLidTimerCount 19 //77 for 2 min 45 sec

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
unsigned volatile char timerCounter = 0; //Timer overflow counter
char EndOfProgram = 0;
char NeedToCloseLid = 0;

//declare functions in main.c file 
void initialize();
void count_gear();
unsigned short readADC(char channel);

void initRamp();    //initialize ramp angle
void ramp_Rotate();    //rotate ramps

void RTC_setTime(void);
void get_RTC_initial();
void get_RTC_final();

void I2C_init();  //initialize I2C
void I2C_sendData(unsigned char char_data);

//dispense fasters array
void Bolt_dispense(int B_max);
void Nut_dispense(int N_max);
void Spacer_dispense(int S_max);
void Washer_dispense(int W_max);

void Bolt_remain(int time);
void Nut_remain(int time);
void Spacer_remain(int time);
void Washer_remain(int time);
void all_remain(int time);
void nut_washer_remain(int time);
void bolt_spacer_remain(int time);
       
/*
 * f_out = f_clk / (4 * prescaler * (MAX_COUNT - TMR0_loadval))
 * 
 * f_clk = FOSC1 = 32MHz (internal oscillator with PLL)
 * MAX_COUNT = 2^16 for 16-bit mode
 * TMR0_loadval = 0
 * Prescale value = 2^8 = 256 (see pg 123 of PIC18F4620 data sheet for assignment)
 *  
 * ==> f_out = 0.477 Hz ==> T_out = 8.097 s(four times longer period for some reason)
 */
void initVibTimer();


//GLCD
void drawTeamName();
void drawBolt();
void drawNut();
void drawSpacer();
void drawWasher();



void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    //OSCCON = 0xF2;  // Use 8 MHz internal oscillator block //oscillator initialize
    /* Use 8 MHz internal oscillator block with PLL enabled --> 32 MHz */      //configure oscillator 32MHZ internal
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS1 = 1;
    OSCTUNEbits.PLLEN = 1; //PLL enabled for INTOSC
    
    
    LATA = 0x00;
    LATB = 0x00; 
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    /********************************* PIN I/O ********************************/
   /* After the states of LATx are known, the data direction registers, TRISx
     * are configured. 0 --> output; 1 --> input. Default is  1. */
    TRISA = 0xFF; // All inputs (this is the default, but is explicated here for learning purposes)
    TRISB = 0xFF;
    TRISC = 0b10000000; /* RC3 is SCK/SCL (SPI/I2C),
                         * RC4 is SDA (I2C),
                         * RC5 is SDA (SPI),
                         * RC6 and RC7 are UART TX and RX, respectively. */
    TRISD = 0b00000001; /* RD0 is the GLCD chip select (tri-stated so that it's
                         * pulled up by default),
                         * RD1 is the GLCD register select,
                         * RD2 is the character LCD RS,
                         * RD3 is the character LCD enable (E),
                         * RD4-RD7 are character LCD data lines. */
    TRISE = 0b00000100; /* RE2 is the SD card chip select (tri-stated so that
                         * it's pulled up by default).
                         * Note that the upper 4 bits of TRISE are special 
                         * control registers. Do not write to them unless you 
                         * read §9.6 in the datasheet */
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    // </editor-fold>
    
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    
    /* Initialize LCD. */
    
    
    initLCD(); 
    initGLCD();  
    
    /* Declare local variables. */
    unsigned char rotation = 0, x = 0, y = 0;
    //glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, WHITE);
    drawTeamName();  
    
    
    while(1){
        //mode = 0: user menu
        if (mode == 0){
            while(1){
                printf("1:date and time");
                __lcd_newline();
                printf("2:Enter Instruction");
                __delay_ms(100);
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
                    __delay_ms(100);
                    __lcd_newline();
                    }
                if (state ==1){
                    initLCD();
                    printf("fastener set:");
                    __lcd_newline();
                    printf("%s",current_set);
                    __delay_ms(100);
                }
        
                if (state == 2){
                    initLCD();
                    printf("number:");
                    __delay_ms(100);
                }
                
                if (state == 3){
                    initLCD();
                    printf("assembly step:%d",assembly_step);
                    __delay_ms(200);
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
                        __delay_ms(100);
                        __lcd_newline();
                    }
                    state = 4;
                }
                if (state == 4){
                    __lcd_home();
                    printf("Press # to start!");
                    __delay_ms(100); 
                }
                if (state == 5){
                     
                    
                    //operation time initial;
                    //get_RTC_initial();  //get initial time variable
                     /* Reset RTC memory pointer. */
                    I2C_init();
                    
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
        
                    
                    
                    initVibTimer();
                    mode = 2;                     //mode change
                    printf("start operation");
                    
                    break;
                    
                }
      
            }
            generate_compartment_array(assembly_step);   //generate again
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
            
            ei();                                                          
            initLCD();
            printf("mode 2");
            __delay_ms(100);
            //Initialize I2C Master with 100 kHz clock. 
            
                
            I2C_init();//Initialize I2C Master with 100 kHz clock. 

            LATCbits.LATC0 = 1;  //set RC0 HIGH-> disable KPD
            TRISCbits.RC0 = 0;

            INT1IE = 0;   //disable interrupt                                   //not sure
            RBIE = 1;  //set RBIE port B to interrupt on change
    
            //dispense 
            initLCD();
            printf("Locating C1");
            //initLCD(); 
            
            //set_data_direction
            TRISBbits.RB5 = 1; // bolt
            TRISBbits.RB7 = 1; // washer
            TRISBbits.RB6 = 1; // spacers
            TRISBbits.RB4 = 1; // nuts
    
            
            I2C_sendData(rotate_gear);  //gear_rotate rotate 360 clockwise to open the handl
                                        //and stop at C0 (when white_tape detected)
            
            //receive data that C0 is found
            
            openHandle_data = '1';
            while(openHandle_data != '0'){
                I2C_Master_Start();
                I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                openHandle_data = I2C_Master_Read(NACK);// Read one char only
                I2C_Master_Stop();
                //read char from arduino
                  
            }
            initLCD();
            printf("C1 is found");
            __lcd_home();
            
               //uncomment
            
        //start dispensing each compartment, i= 0; i<8
        
            I2C_init();
            generate_compartment_array(assembly_step);
            int compart_id = 0;
            while(NeedToCloseLid != 1 && compart_id < 8){ 
                initLCD();
                printf("processing C%d",(compart_id+1));
                __delay_ms(100);
                
                if (compartment_array[compart_id] == 1){
                    B_counter = 0;   //reset variables
                    N_counter = 0;
                    S_counter = 0;
                    W_counter = 0;
                    
                    if (NeedToCloseLid != 1) 
                        Bolt_dispense(B_array[compart_id]);
                        
                        
                    if (NeedToCloseLid != 1) 
                        Nut_dispense(N_array[compart_id]);
                        
                        
                    if (NeedToCloseLid != 1) 
                        Spacer_dispense(S_array[compart_id]);
                        
                    if (NeedToCloseLid != 1) 
                        Washer_dispense(W_array[compart_id]);
                        
                }
               
                printf("done C%d",compart_id);
                if (NeedToCloseLid != 1 && compart_id < 7){
                    I2C_sendData(rotate_1compartment);
                    while(NeedToCloseLid != 1){
                        I2C_Master_Start();
                        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                        openHandle_data = I2C_Master_Read(NACK);// Read one char only
                        I2C_Master_Stop();
                        if (openHandle_data == '1'){
                            openHandle_data == 'a';
                            break;
                        }
                    }
                }
                compart_id ++;
            }
        
  

        /*********dispense remaining fasteners******/
        /**************close the lid********/
        I2C_sendData(close_handle);
        
        
        __delay_ms(2500);
       
        /****** servo_ramp rotate******/
        //rotate _ramp to dispense the remaining fasteners to the bottom reservoirs.
        I2C_sendData(servo_ramp);
        //dispensing the remain fasteners, and rotate counterclockwise 360+45 + to close the lid
        // ********** Dispense all at the same time ************
        __delay_ms(100);
        
//        if (EndOfProgram != 1){
//            nut_washer_remain(spacingTime);
//        }
//        if (EndOfProgram != 1){
//            bolt_spacer_remain(spacingTime);
//        }
        
//        if (EndOfProgram != 1){
//            all_remain(spacingTime);
//        }
        
        // ********* Dispense Remaining One by One *************
        if (EndOfProgram != 1){
            Nut_remain(spacingTime);
            //spacingTime variable initialized in keypad.h
        }
        if (EndOfProgram != 1){
            Washer_remain(spacingTime);
        }
        if (EndOfProgram != 1){
            Spacer_remain(spacingTime);
        }
        if (EndOfProgram != 1){
            Bolt_remain(spacingTime);   
        }
//        
        /*    
        while(1){
            I2C_Master_Start();
            I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
            nuts_data = I2C_Master_Read(NACK);// Read one char only
            I2C_Master_Stop();
            if (nuts_data == close_handle){    //lid is closed
                break;
            } 
        }
         */ 
        initLCD();
        __lcd_home();
        printf("Terminate!");
        __delay_ms(500);
        
        //__delay_ms(2000);
        I2C_init();
        
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
        
        
        
        
        initLCD();
        printf("Terminate!");
        __delay_ms(500);
        __lcd_home();        
            
        //store final operation_time variable
        //get_RTC_final();
        
        drawTeamName();
        
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
        
        ei();
        LATCbits.LATC0 = 0;  //set RC0 LOW-> enable KPD
        TRISCbits.RC0 = 0;

        RBIE = 0;  //diasble interrupt
        INT1IE = 1;
        
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
            __lcd_newline();
            printf("4:return");
                  
            __delay_ms(100);
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
        //if(temp == 'A'){
        //    state = prev_state;
        //    INT1IF = 0; 
        //    return;
        //}
            
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
                    __delay_ms(200);
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
                __delay_ms(200);
        
                
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
                __lcd_home();
                initLCD();
                for (i = 0; i<8; i++){ 
                    __lcd_clear();
                    __lcd_home(); 
                    printf("C%d:B%d,N%d", B_array[i],N_array[i]);
                    __lcd_newline();
                    printf("    S%d,W%d", S_array[i], W_array[i]);
                    __delay_ms(500);
                    //B_total_dispensed += B_array[i];
                    //N_total_dispensed += N_array[i];
                    //S_total_dispensed += S_array[i];
                    //W_total_dispensed += W_array[i];
                    
                }
                

                __delay_ms(400);
                initLCD();
                
                printf("Bolt_remain:%d",B_remain);
                __delay_ms(500);
                initLCD();
                
                printf("Nut_remain:%d",N_remain);
                __delay_ms(500);
                
                initLCD();
                printf("Spacer_remain:%d",S_remain);
                __delay_ms(500);
                
                initLCD();
                printf("Washer_remain:%d",W_remain);
                __delay_ms(500);
                
                initLCD();
                
                __lcd_clear();
                printf("Done");
                __delay_ms(100);
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
                    __delay_ms(500);
                
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
                //if (temp == 'A'){
                //    state = prev_state;
                //}
            
                if (temp == 'A'){
                     __lcd_newline();
                    putch('B');
                    strcpy(temp_set,"B");
                    strcat(current_set,temp_set);
                    counter++;
                }
            
                if(temp == 'B'){
                     __lcd_newline();
                    putch('N');
                    strcpy(temp_set,"N");
                    strcat(current_set,temp_set);
                    counter++;
                }
            
                if(temp == 'C'){
                    __lcd_newline();
                    putch('S');
                    
                    strcpy(temp_set,"S");
                    strcat(current_set,temp_set);
                    counter++;
                }
                if (temp == 'D'){
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
                    __delay_ms(80);
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
                                __delay_ms(100);
                                //__lcd_newline();
                                printf("%s",current_set);
                                
                                strcpy(current_set,""); 
                                counter = 0;
                                break;
                                
                            }
                    }
                    if (valid != 1){
                            
                            initLCD();
                            printf("wrong set!");
                            printf("%s",current_set);
                            strcpy(current_set,"");
                            __delay_ms(100);
                            counter = 0;
                            valid = 0;
                        }
                    valid = 0;
                
                }
            
             
            if (counter >= 5){
                
                initLCD();
                printf("wrong!");
                //printf(counter);
                __delay_ms(100);
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
                __delay_ms(100);
                printf("Processing..."); 
                
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
                        __delay_ms(100);
                }
                
                
                is_valid();
                
                if ( check() == 0){
                    initLCD();
                    __lcd_home();
                    printf("TOO MANY");
                    
                    __delay_ms(100);
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
        
        // state 4: wait for start button
        if(state == 4){
            if(keys[keypress] == '#')
                state = 5;
            }
                
            B=0;N=0;S=0;W=0;
            total_number = 0;
            
            INT1IF = 0; 
            return;
        }
                
                

        //__lcd_home();
        
        //INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
        //return;
    
    
    if (RBIF){  //interrupt for fastener dispense (interrupt on change))

        B_input = PORTBbits.RB5;   //bolts     
        N_input = PORTBbits.RB6;   //nuts
        S_input = PORTBbits.RB4;  //spacer
        W_input = PORTBbits.RB7;  //washer
        
        
        
        if (B_input == 1){
            B_spacingTime = 0;
            initLCD();
            printf("bolt_interrupt");
            __lcd_home();
            B_counter++;
            
        }
        
        
        if (N_input == 1){
            N_spacingTime = 0;
            initLCD();
            printf("nut_interrupt");
            __lcd_home();
            N_counter++;
        }
        
        if (S_input == 1){
            S_spacingTime = 0;
            S_counter++;
            initLCD();
            
            printf("spacer_interrupted");
            __lcd_home();
        }
        
        if (W_input == 1){
            W_spacingTime = 0;
            initLCD();
           printf("washer_interrupted");
            __lcd_home();
            W_counter++;
            //printf("%d",W_count);
            //__lcd_home();
        }
        initLCD();
        //printf("interrupted");
        __lcd_home();
        //initLCD();
        //printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        //__lcd_home();
        

        RBIF = 0;
        return;
    }
    if(TMR0IE && TMR0IF){ 
        timerCounter ++; 
        if (timerCounter >= CloseLidTimerCount){
            NeedToCloseLid = 1;
        }
        if(timerCounter >= EndProgramTimerCount){
            timerCounter = 0;
            EndOfProgram = 1;
        }
        
        TMR0IF = 0; //clear flag
    }

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
        return;
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
        return;
        
}



void I2C_init(){
    I2C_Master_Init(100000);          //change to 80000
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    return;
}

void I2C_sendData(unsigned char char_data){
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write(char_data); // rotate servo and find C0
    I2C_Master_Stop();
    return;
}


//dispense fasteners functions
void Bolt_dispense(int B_max){
    if (B_max == 0){
        return;
    }
    //dispense bolt
    drawBolt();
    __delay_ms(100);
    I2C_sendData('5'); // rotate bolt motor 
    while(NeedToCloseLid != 1 && B_counter < B_max){
        __lcd_clear();
        __lcd_home(); 
        printf("B:%d",B_counter);
    }
    I2C_sendData('6');
    __delay_ms(100);
}

void Nut_dispense(int N_max){
    if (N_max == 0){
        return;
    }
    drawNut();
    __delay_ms(100);
    I2C_sendData('7');
    N_counter = 0;
    while(NeedToCloseLid != 1 && N_counter < N_max){
        
        __lcd_home(); 
        __lcd_clear();
        printf("N:%d",N_counter);
    }
    I2C_sendData('8');
    
}

void Spacer_dispense(int S_max){
    if (S_max == 0){
        return;
    }
    drawSpacer();
    __delay_ms(100);
    I2C_sendData('9'); 
    S_counter = 0;
    while(NeedToCloseLid != 1 && S_counter < S_max){
        
        __lcd_home(); 
        __lcd_clear();
        printf("S:%d", S_counter);
    }
    I2C_sendData(10);
}

void Washer_dispense(int W_max){
    if (W_max == 0){
        return;
    }
    drawWasher();
    __delay_ms(100);
    I2C_sendData(11); 
    W_counter = 0;
    while(NeedToCloseLid != 1 && W_counter < W_max){
        __lcd_clear();
        __lcd_home(); 
        printf("W:%d",W_counter);
    }
    I2C_sendData(12);
    return;
}

void nut_washer_remain(int time){ 
    drawWasher();
    __delay_ms(50);
    I2C_sendData(11);
    __delay_ms(1000); 
    
    drawNut();
    __delay_ms(50);
    I2C_sendData('7');
    char timeout = 0;
    N_spacingTime = 0;
    W_spacingTime = 0;
    while(EndOfProgram != 1 && timeout != 1){
        timeout = 1;
        N_spacingTime += 30;
        W_spacingTime += 30;
        initLCD();
        __lcd_home();
        printf("B:%d,N:%d,S:%d,W:%d",B_counter,N_counter,S_counter,W_counter);
        if(N_spacingTime > time){
            I2C_sendData('8');
        }
        else{
            timeout = 0;
        }
        if(W_spacingTime > time){
            I2C_sendData(12);
        }
        else{
            timeout = 0;
        }
    }
    I2C_sendData('8');
    I2C_sendData(12); 
    N_remain = N_counter;
    W_remain = W_counter;
    
}
void bolt_spacer_remain(int time){
    drawBolt();
    __delay_ms(50);
    I2C_sendData('5');
    __delay_ms(1000);
    drawSpacer();
    __delay_ms(50);
    I2C_sendData('9'); 
    char timeout = 0;
    B_spacingTime = 0;
    S_spacingTime = 0;
    while(EndOfProgram != 1 && timeout != 1){
        timeout = 1;
        B_spacingTime += 30;
        S_spacingTime += 30;
        initLCD();
        __lcd_home();
        printf("B:%d,N:%d,S:%d,W:%d",B_counter,N_counter,S_counter,W_counter);
        if(B_spacingTime > time){
            I2C_sendData('6');
        }
        else{
            timeout = 0;
        }
        if(S_spacingTime > time){
            I2C_sendData(10);
        }
        else{
            timeout = 0;
        }
    }
    I2C_sendData('6');
    I2C_sendData(10); 
    
    B_remain = B_counter;
    S_remain = S_counter;
}


void all_remain(int time){
    I2C_sendData('5');
    __delay_ms(500);
    I2C_sendData('7');
    __delay_ms(500);
    I2C_sendData('9');
    __delay_ms(500);
    I2C_sendData(11);
    char timeout = 0;
    while(EndOfProgram!= 1 && timeout != 1){
        timeout = 1;
        B_spacingTime += 30;
        N_spacingTime += 30;
        W_spacingTime += 30;
        S_spacingTime += 30;
        initLCD();
        __lcd_home();
        printf("B:%d,N:%d,S:%d,W:%d",B_counter,N_counter,S_counter,W_counter);
        if(B_spacingTime > time){
            I2C_sendData('6');
        }
        else{
            timeout = 0;
        }
        if(N_spacingTime > time){
            I2C_sendData('8');
        }
        else{
            timeout = 0;
        }
        if(S_spacingTime > time){
            I2C_sendData(10);
        }
        else{
            timeout = 0;
        }
        if(W_spacingTime > time){
            I2C_sendData(12);
        }
        else{
            timeout = 0;
        }
    }
    I2C_sendData('6');
    I2C_sendData('8');
    I2C_sendData(10);
    I2C_sendData(12);
    __lcd_home();
    printf("Program Terminates");
    
}

void Bolt_remain(int time){
     drawBolt();
    __delay_ms(100);
    I2C_sendData('5'); // rotate bolt motor
    while(EndOfProgram!= 1 && B_spacingTime < time){
        __lcd_home(); 
        __lcd_clear();
        B_spacingTime +=30;
        printf("B:%d",B_counter);
    }
    B_remain = B_counter;
    I2C_sendData('6');
    if(EndOfProgram != 1){
        __delay_ms(100);
    }
}


void Nut_remain(int time){
    drawNut();
    __delay_ms(100);
    I2C_sendData('7'); // rotate bolt motor
    while(EndOfProgram!= 1 && N_spacingTime < time){
        __lcd_clear();
        __lcd_home(); 
        N_spacingTime +=30;
        printf("N:%d",N_counter);
    }
    N_remain = N_counter;
    I2C_sendData('8');
    if(EndOfProgram != 1){
        __delay_ms(100);
    }
}


void Spacer_remain(int time){
    drawSpacer();
    __delay_ms(100);
    I2C_sendData('9'); // rotate bolt motor
    while(EndOfProgram != 1 && S_spacingTime < time){
        __lcd_clear();
        __lcd_home(); 
        S_spacingTime +=30;
        printf("S:%d",S_counter);
    }
    S_remain = S_counter;
    I2C_sendData(10);
    if(EndOfProgram != 1){
        __delay_ms(100);
    }
}


void Washer_remain(int time){
    drawWasher();
    __delay_ms(100);
    I2C_sendData(11); // rotate bolt motor
    while(EndOfProgram != 1 && W_spacingTime < time){
        __lcd_clear();
        __lcd_home(); 
        W_spacingTime +=30;
        printf("W:%d",W_counter);
    }
    W_remain = W_counter;
    I2C_sendData(12);
    if(EndOfProgram != 1){
        __delay_ms(100);
    }
}

/*
 * f_out = f_clk / (4 * prescaler * (MAX_COUNT - TMR0_loadval))
 * 
 * f_clk = FOSC1 = 32MHz (internal oscillator with PLL)
 * MAX_COUNT = 2^16 for 16-bit mode
 * TMR0_loadval = 0
 * Prescale value = 2^8 = 256 (see pg 123 of PIC18F4620 data sheet for assignment)
 *  
 * ==> f_out = 0.477 Hz ==> T_out = 2.097 s
 */
void initVibTimer(){
    /* Enable Timer Interrupt */
    INTCONbits.TMR0IE = 1;
    ei();
    
    T0CONbits.T08BIT = 0;   // 16-bit mode selected
    T0CONbits.T0CS = 0;     // Internal clock selected (timer mode ON)
    T0CONbits.PSA = 0;      // Prescaler assigned
    T0CONbits.T0PS0 = 1;    // Prescaler values
    T0CONbits.T0PS1 = 1 ;    // Prescaler values
    T0CONbits.T0PS2 = 1;    // Prescaler values
    
    T0CONbits.TMR0ON = 1;   // Turn ON the timer
}


//GLCD

void drawTeamName(){
    spiInit(4);
    __delay_ms(20);
    glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, BLACK);
    //T
    glcdDrawRectangle(5*4, 11*4, 9*4, 11*4, WHITE);
    glcdDrawRectangle(8*4, 9*4, 11*4, 16*4, WHITE);
    //3
    glcdDrawRectangle(12*4, 17*4, 9*4, 11*4, WHITE);
    glcdDrawRectangle(16*4, 17*4, 11*4, 16*4, WHITE);
    glcdDrawRectangle(12*4, 16*4, 12*4, 13*4, WHITE);
    glcdDrawRectangle(12*4, 16*4, 14*4, 16*4, WHITE);
    //4
    glcdDrawRectangle(18*4, 19*4, 9*4, 14*4, WHITE);
    glcdDrawRectangle(19*4, 23*4, 12*4, 14*4, WHITE);
    glcdDrawRectangle(21*4, 22*4, 9*4, 16*4, WHITE);

    //heat
    glcdDrawRectangle(24*4, 25*4, 10*4, 13*4, RED);
    glcdDrawRectangle(25*4, 27*4, 9*4, 14*4, RED);
    glcdDrawRectangle(27*4, 28*4, 10*4, 15*4, RED);

    glcdDrawRectangle(28*4, 30*4, 9*4, 14*4, RED);
    glcdDrawRectangle(30*4, 31*4, 10*4, 13*4, RED);
    I2C_Master_Init(100000); 
}



void drawWasher(){
    spiInit(4);
    __delay_ms(20);
    glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, BLACK);
    //draw outer circle
    
     glcdDrawRectangle(5*4,6*4, 13*4, 20*4, WHITE);
     glcdDrawRectangle(6*4,7*4, 11*4, 13*4, WHITE);
     glcdDrawRectangle(7*4,8*4, 9*4, 11*4, WHITE);

     glcdDrawRectangle(8*4,9*4, 8*4, 9*4, WHITE);
     glcdDrawRectangle(9*4,11*4, 7*4, 8*4, WHITE);
     glcdDrawRectangle(11*4,13*4, 6*4, 7*4, WHITE);

     glcdDrawRectangle(13*4,20*4, 5*4, 6*4, WHITE);
     glcdDrawRectangle(20*4,22*4, 6*4, 7*4, WHITE);
     glcdDrawRectangle(22*4,24*4, 7*4, 8*4, WHITE);

     glcdDrawRectangle(24*4,25*4, 8*4, 9*4, WHITE);

     glcdDrawRectangle(25*4,26*4, 9*4, 11*4, WHITE);
    glcdDrawRectangle(26*4,27*4, 11*4, 13*4, WHITE);
    glcdDrawRectangle(27*4,28*4, 13*4, 20*4, WHITE);

    glcdDrawRectangle(26*4,27*4, 20*4, 22*4, WHITE);
    glcdDrawRectangle(27*4,28*4, 22*4, 24*4, WHITE);
    glcdDrawRectangle(26*4,27*4, 20*4, 22*4, WHITE);

    glcdDrawRectangle(25*4,26*4, 22*4, 24*4, WHITE);
    glcdDrawRectangle(24*4,25*4, 24*4, 25*4, WHITE);
    glcdDrawRectangle(22*4,24*4, 25*4, 26*4, WHITE);

    glcdDrawRectangle(20*4,22*4, 26*4, 27*4, WHITE);
    glcdDrawRectangle(13*4,20*4, 27*4, 28*4, WHITE);
    glcdDrawRectangle(11*4,13*4, 26*4, 27*4, WHITE);

    glcdDrawRectangle(9*4,11*4, 25*4, 26*4, WHITE);
    glcdDrawRectangle(8*4,9*4, 24*4, 25*4, WHITE);
    glcdDrawRectangle(7*4,8*4, 22*4, 24*4, WHITE);

    glcdDrawRectangle(6*4,7*4, 20*4, 22*4, WHITE);

    //inner circle

    glcdDrawRectangle(13*4,14*4, 14*4, 17*4, WHITE);
    glcdDrawRectangle(14*4,15*4, 13*4, 14*4, WHITE);
    glcdDrawRectangle(6*4,7*4, 11*4, 13*4, WHITE);

    glcdDrawRectangle(15*4,18*4, 12*4, 13*4, WHITE);
    glcdDrawRectangle(18*4,19*4, 13*4, 14*4, WHITE);
    glcdDrawRectangle(19*4,20*4, 14*4, 17*4, WHITE);
    glcdDrawRectangle(18*4,19*4, 17*4, 18*4, WHITE);

    glcdDrawRectangle(15*4,18*4, 18*4, 19*4, WHITE);
    glcdDrawRectangle(14*4,15*4, 16*4, 17*4, WHITE);
    glcdDrawRectangle(13*4,14*4, 14*4, 17*4, WHITE);
    I2C_Master_Init(100000); 



     
}

void drawBolt(){
    spiInit(4);
    __delay_ms(20);
    glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, BLACK);
    glcdDrawRectangle(5*4,9*4, 8*4, 20*4, WHITE);
    glcdDrawRectangle(6*4,8*4, 9*4, 19*4, WHITE);

    glcdDrawRectangle(8*4,28*4, 11*4, 17*4, WHITE);
    glcdDrawRectangle(9*4,27*4, 12*4, 16*4, WHITE);
    I2C_Master_Init(100000); 

}

void drawNut(){
    spiInit(4);
    __delay_ms(20);
    glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, BLACK);
    glcdDrawRectangle(13*4,14*4, 14*4, 17*4, WHITE);
    glcdDrawRectangle(14*4,15*4, 13*4, 14*4, WHITE);
    glcdDrawRectangle(6*4,7*4, 11*4, 13*4, WHITE);

    glcdDrawRectangle(15*4,18*4, 12*4, 13*4, WHITE);
    glcdDrawRectangle(18*4,19*4, 13*4, 14*4, WHITE);
    glcdDrawRectangle(19*4,20*4, 14*4, 17*4, WHITE);
    glcdDrawRectangle(18*4,19*4, 17*4, 18*4, WHITE);

    glcdDrawRectangle(15*4,18*4, 18*4, 19*4, WHITE);
    glcdDrawRectangle(14*4,15*4, 16*4, 17*4, WHITE);
    glcdDrawRectangle(13*4,14*4, 14*4, 17*4, WHITE);

    //draw hole
    glcdDrawRectangle(16*4,17*4, 15*4, 16*4, WHITE);
    I2C_Master_Init(100000); 
}


void drawSpacer(){
    spiInit(4);
    __delay_ms(20);
    glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, BLACK);
    glcdDrawRectangle(6*4,7*4, 12*4, 17*4, WHITE);
    glcdDrawRectangle(16*4,17*4, 15*4, 16*4, WHITE);
    glcdDrawRectangle(7*4,8*4, 11*4, 12*4, WHITE);

    glcdDrawRectangle(8*4,23*4, 10*4, 11*4, WHITE);

    //hole
    glcdDrawRectangle(8*4,9*4, 13*4, 15*4, WHITE);
    glcdDrawRectangle(9*4,10*4, 14*4, 16*4, WHITE);
    glcdDrawRectangle(10*4,11*4, 11*4, 12*4, WHITE);

    glcdDrawRectangle(11*4,12*4, 12*4, 17*4, WHITE);
    glcdDrawRectangle(7*4,8*4, 17*4, 18*4, WHITE);
    glcdDrawRectangle(10*4,11*4, 17*4, 18*4, WHITE);

    glcdDrawRectangle(8*4,23*4, 18*4, 19*4, WHITE);
    glcdDrawRectangle(23*4,24*4, 17*4, 18*4, WHITE);

    glcdDrawRectangle(23*4,24*4, 11*4, 12*4, WHITE);
    glcdDrawRectangle(24*4,25*4, 12*4, 17 *4, WHITE);
    I2C_Master_Init(100000); 
}