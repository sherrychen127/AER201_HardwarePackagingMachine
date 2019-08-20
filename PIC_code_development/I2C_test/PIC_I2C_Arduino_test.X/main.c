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
const char array[] = "10";

int state = 0;

int B_counter = 0;
int N_counter = 0;
int S_counter = 0;
int W_counter = 0;


int B_remain = 0;

int max = 4;
unsigned short analog_result;
int i;
//const char PR_value = "01";

//unsigned char ReadSensor(unsigned char ch){
//    ADCON0 = 0x00; //clear ADCON0
//    ADCON0 = (ch << 2);
//    ADON = 1;
    
//    ADCON0bits.GO = 1; // Initiate sampling
//    while(ADCON0bits.GO_NOT_DONE){  continue;   }
//   // __delay_ms(500);
//    ADON = 0;
//    return ADRESH;
    
//}
unsigned short readADC(char channel);
void motorStart_0();
void motorStop_0();
void motorStart_1();
void motorStop_1();
void motorStart_2();
void motorStop_2();
void motorStart_3();
void motorStop_3();




//void servoRotate80();
//void servoRotate0();

//void servoRotate80_2();
//void servoRotate0_2();

//void servoRotate80_3();
//void servoRotate0_3();

//void servoRotate80_4();
//void servoRotate0_4();



void servoRotate_clockwise();
void servoRotate_ConStop();
void servoRotate_counter();



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
    
    /* Write the address of the slave device, that is, the Arduino Nano. Note
     * that the Arduino Nano must be configured to be running as a slave with
     * the same address given here. Note that other addresses can be used if
     * desired, as long as the change is reflected on both the PIC and Arduino
     * ends. */
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
    /* Initialize local variables. */
    unsigned char mem[3]; // Initialize array to check for triple-A sequence
    unsigned char counter = 0; // Increments each time a byte is sent
    unsigned char keypress; // Stores the data corresponding to the last key press
    unsigned char data; // Holds the data to be sent/received
    static bit SEND;
    SEND = 1;
    
    /* Main loop. */
    //while(1) {
        //if(SEND){
            //while (PORTBbits.RB1 == 0) {    continue;   }
            //keypress = (PORTB & 0xF0) >> 4;
            //while (PORTBbits.RB1 == 1) {    continue;   }
            //data = keys[keypress];
            
            I2C_Master_Start(); // Start condition
            I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
            I2C_Master_Write(14); // Write key press data
            I2C_Master_Stop();

            
            
            INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    
    /* Initialize LCD. */
    initLCD();
    __delay_ms(4000);
    __delay_ms(4000);
    __delay_ms(4000);
    

    //I2C_Master_Init(100000); 
    //I2C_Master_Start(); // Start condition
    
    /* Write the address of the slave device, that is, the Arduino Nano. Note
     * that the Arduino Nano must be configured to be running as a slave with
     * the same address given here. Note that other addresses can be used if
     * desired, as long as the change is reflected on both the PIC and Arduino
     * ends. */
    //I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    //I2C_Master_Stop();
    

   
          /*
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('2'); // Write key press data
    I2C_Master_Stop();
    */
    
    
    
 
       
    
       
    
        
    //}
    
    
    
    initLCD();
    printf("Bolts:%d",B_counter);
    __delay_ms(1000);
    
    initLCD();
    printf("Nuts:%d",N_counter);
    __delay_ms(1000);
    
    initLCD();
    printf("Spacer:%d",S_counter);
    __delay_ms(1000);
    
    initLCD();
    printf("Washers:%d",W_counter);
    __delay_ms(1000);
    
    
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
    return analog_result;
    
    //return (ADRESH << 8) | ADRESL; // Return result as a 16-bit value
}



void motorStart_0(){
    
        LATCbits.LATC0 = 1;  //RC0 HIGH
        TRISCbits.RC0 = 0;
        //LATAbits.LATA2 = 0;  //RC2 LOW
        __delay_ms(200);//2 seconds delay
    
}

void motorStop_0(){
    LATCbits.LATC0 = 0;  //RC0 LOW
    TRISCbits.RC0 = 0;
    //LATAbits.LATA2 = 0;  //RC2 LOW
    __delay_ms(200);//2 seconds delay
}


void motorStart_1(){
    
        LATCbits.LATC1 = 1;  //RC0 HIGH
        TRISCbits.RC1 = 0;
        //LATAbits.LATA2 = 0;  //RC2 LOW
        __delay_ms(200);//2 seconds delay
    
}

void motorStop_1(){
    LATCbits.LATC1 = 0;  //RC0 LOW
    TRISCbits.RC1 = 0;
    //LATAbits.LATA2 = 0;  //RC2 LOW
    __delay_ms(200);//2 seconds delay
}

//motor_2
void motorStart_2(){
    
        LATCbits.LATC2 = 1;  //RC0 HIGH
        TRISCbits.RC2 = 0;
        //LATAbits.LATA2 = 0;  //RC2 LOW
        __delay_ms(200);//2 seconds delay
    
}

void motorStop_2(){
    LATCbits.LATC2 = 0;  //RC0 LOW
    TRISCbits.RC2 = 0;
    //LATAbits.LATA2 = 0;  //RC2 LOW
    __delay_ms(200);//2 seconds delay
}

//motor_3

void motorStart_3(){
    
        LATCbits.LATC5 = 1;  //RC0 HIGH
        TRISCbits.RC5 = 0;
        //LATAbits.LATA2 = 0;  //RC2 LOW
        __delay_ms(200);//2 seconds delay
    
}

void motorStop_3(){
    LATCbits.LATC5 = 0;  //RC0 LOW
    TRISCbits.RC5 = 0;
    //LATAbits.LATA2 = 0;  //RC2 LOW
    __delay_ms(200);//2 seconds delay
}


//continuous servo

void servoRotate_clockwise(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(800); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(19200);
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
    for (i = 0; i<50; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(2200); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(17800);
    }
    //clockwise;
    
}