 /*
 * File:   main.c
 * Author: Michael Ding
 *
 * Created on July 18, 2016, 12:11 PM
 * 
 * Edited by Tyler Gamvrelis, summer 2017
 * 
 * Description: Demonstration of communication between the primary PIC and the
 *              Arduino Nano, via I2C. To see the results on the Arduino Nano
 *              side, open the Arduino sample program Arduino_I2C_PIC. If the
 *              PIC receives a triple-A sequence from the keypad, it changes
 *              from being a transmitter to being a receiver that displays data
 *              on the character LCD. To change it back, reset the PIC.
 * 
 * Preconditions:
 *   1. PIC-Arduino link switches are enabled (ON) for A4 and A5 of the Arduino
 *      Nano (RC4 and RC3 for the primary PIC, respectively)
 *   2. PIC and Arduino Nano agree on the Arduino Nano's slave address (i.e. the
 *      same slave address is used in software)
 *   3. A PC is connected if the Arduino Nano serial monitor is to be used
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "I2C.h"

/***** Constants *****/
const char keys[] = "123A456B789C*0#D";
char openHandle_data;
char nuts_data;  // countain the received char byte from arduino



unsigned char rotate_gear = '0';
unsigned char rotate_1compartment = '1';
unsigned char B_dispense = '2';
unsigned char N_dispense = '3';
unsigned char S_dispense = '4';

unsigned char motorStart_0 = '5';
unsigned char motorStop_0 = '6';

unsigned char motorStart_1 = '7';
unsigned char motorStop_1 = '8';

unsigned char motorStart_2 = '9';   //
unsigned char motorStop_2 = 10;

unsigned char motorStart_3 = 11;
unsigned char motorStop_3 = 12;

unsigned char servo_ramp = 13;
unsigned char close_handle = 14;






int N_counter = 0; //nuts counter
int N_remain = 0;
int N_max = 4; //arbitrary max number for nuts
int N_spacingTime = 0;


int B_counter = 0;
int B_remain = 0;
int B_max = 4;
int B_spacingTime = 0;

int S_counter = 0;
int S_remain = 0;
int S_max = 4;
int S_spacingTime = 0;

int W_counter = 0;
int W_remain = 0;
int W_max = 4;
int W_spacingTime = 0;



unsigned short analog_result;

void I2C_sendData(unsigned char char_data);
unsigned short readADC(char channel);

void main(void) {

    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    //OSCCON = 0xF2;
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
    
    
    I2C_sendData('1');
    while(1){
        
        //__delay_ms(1000);
        I2C_Master_Start();
        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
        nuts_data = I2C_Master_Read(NACK);// Read one char only
        I2C_Master_Stop();
        if (nuts_data == '1'){
            __delay_ms(1000);
            //send '3' to arduino start dispensing the next one 
            I2C_sendData('1');
        }
    }
    
    
    //dispense Spacer
    /*
    I2C_sendData(motorStart_2);
    while(1){
        if (S_counter >= S_max){
            I2C_sendData(motorStop_0);
            break;
        }
        
        if (readADC(2)<=250 ){   //A0
            
            S_counter ++;
            initLCD();
            printf("%d", S_counter);
            
            }
    }
     */ 
    
     //dispense Bolts
    initLCD();
    printf("B_counter:%d",B_counter);
            
    I2C_sendData(B_dispense);
    while(1){
        I2C_sendData(motorStart_0); //start nuts_motor  '2'
        if (B_counter >= B_max){
            I2C_sendData(motorStop_0);
            //break;
        }
        

        I2C_Master_Start();
        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
        nuts_data = I2C_Master_Read(NACK);// Read one char only
        I2C_Master_Stop();
        if (nuts_data == '2'){
            B_counter ++;
            initLCD();
            printf("B_count:%d", B_counter);
            //send '3' to arduino start dispensing the next one 
            I2C_sendData(B_dispense);
        }
    }
    B_counter = 0;
    
    initLCD();
   
    printf("bolts dispensed");
    __delay_ms(1000);
    __lcd_home();
    
    
    
    
    
    //dispense nuts
    initLCD();
    printf("N_counter:%d",N_counter);
    I2C_sendData(N_dispense);
    while(1){
        I2C_sendData(motorStart_1); //start nuts_motor
        if (N_counter >= N_max){
            I2C_sendData(motorStop_1);
            break;
        }
        

        I2C_Master_Start();
        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
        nuts_data = I2C_Master_Read(NACK);// Read one char only
        I2C_Master_Stop();
        if (nuts_data == '3'){
            N_counter ++;
            
            initLCD();
            printf("%d", N_counter);
            
            //send '3' to arduino start dispensing the next one 
            I2C_sendData(N_dispense);
           
        }
    }
    N_counter = 0;
    
    initLCD();
    
    printf("nuts dispensed");
    __delay_ms(1000);
    __lcd_home();
    
    
    
     
    //dispense Spacer
    initLCD();
    printf("S_counter:%d",S_counter);
    I2C_sendData(S_dispense);
    while(1){
        I2C_sendData(motorStart_2); //start nuts_motor  '2'
        if (S_counter >= S_max){
            I2C_sendData(motorStop_2);
            break;
        }
        

        I2C_Master_Start();
        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
        nuts_data = I2C_Master_Read(NACK);// Read one char only
        I2C_Master_Stop();
        if (nuts_data == '4'){
            S_counter ++;
            
            initLCD();
            printf("%d", S_counter);
            
            //send '3' to arduino start dispensing the next one 
            I2C_sendData(S_dispense);
           
        }
    }
    S_counter = 0;
    
    initLCD();
   
        printf("Spacer dispensed");
        __delay_ms(1000);
        __lcd_home();
    
    
        
    //dispense washer
        
    initLCD();
    printf("%d",W_counter);
    __delay_ms(100);
    I2C_sendData(motorStart_3);
    
    while(1){
        
        if (W_counter >= W_max){
            W_counter = 0;
            I2C_sendData(motorStop_3);
            break;
        }
        
        
        if (readADC(3)<=250 ){   //800
            //motorStart_0();  
            W_counter ++;
            initLCD();
            printf("%d", W_counter);
            
            }
        
          
    }
    //*/
    
    initLCD();
    printf("done");
    __delay_ms(800);
        
        
    
        //rotate servo
    I2C_sendData(13);
    __delay_ms(1000);
    
    
    //dispense remaining fasteners
    //dispense bolts
    initLCD();
    printf("B_remain:%d",B_remain);
            
    I2C_sendData(B_dispense);
    while(1){
        I2C_sendData(motorStart_0); //start nuts_motor  '2'
        if (B_spacingTime >= 30000){ //15sec
            I2C_sendData(motorStop_0);  
            break;
        }
        

        I2C_Master_Start();
        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
        nuts_data = I2C_Master_Read(NACK);// Read one char only
        I2C_Master_Stop();
        if (nuts_data == '2'){
            B_remain ++;
            
            initLCD();
            printf("B_remain:%d", B_remain);
            
            //send '3' to arduino start dispensing the next one 
            I2C_sendData(B_dispense);
           
        }
    }
    //B_remain = 0;
    
    initLCD();
   
    printf("bolts remained:%d",B_remain);
    __delay_ms(1000);
    __lcd_home();
    
    
    
    //washers
    initLCD();
    I2C_sendData(motorStart_3);
    
    W_spacingTime = 0;
    initLCD();
    printf("%d", W_remain);
    while (1){

        if (W_spacingTime >= 30000){ //15sec
            I2C_sendData(motorStop_3);
            
            break;
        }
        
        if (readADC(3)<=250 ){   //800   32800
            //motorStart_0();  
            W_remain ++;
            initLCD();
            printf("%d", W_remain);
           // __delay_ms(1);
            W_spacingTime = 0;
                
            }
       //printf("RA2: %.3x", readADC(3));
       //__lcd_newline();
   
        __lcd_newline();
        printf("%d",W_spacingTime);
        
        __lcd_home();
        W_spacingTime +=200;
    }
    
        
    
    
    
    
    
    
    
    
    
    
    //send data to rotate the compartment
    /*
            I2C_Master_Start(); // Start condition
            I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
            I2C_Master_Write('0'); // rotate servo and find C0
            I2C_Master_Stop();
            
            */
            //break;
            //__delay_ms(1000);
            /*
            I2C_Master_Start(); // Start condition
            I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
            I2C_Master_Write('b'); // Write key press data
            I2C_Master_Stop();
            __delay_ms(1000);
             * 
             *
            */
            
            
            //receive data
            
            
            
            //receive data that C0 is found
    /*
            while(1){
                I2C_Master_Start();
                I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
                openHandle_data = I2C_Master_Read(NACK);// Read one char only
                I2C_Master_Stop();
                
                if (openHandle_data == '0'){
                    initLCD();
                    printf("C0 is found");
                    __lcd_home();
                    __delay_ms(100);
                    break;
                }
            }
     */ 
      
    
}


void I2C_sendData(unsigned char char_data){
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write(char_data); // rotate servo and find C0
    I2C_Master_Stop();
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
    analog_result = ADRESL + (ADRESH*256);
    //return analog_result;
    
    return (ADRESH << 8) | ADRESL; // Return result as a 16-bit value
}