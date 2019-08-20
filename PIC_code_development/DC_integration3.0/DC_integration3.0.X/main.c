/*
 * File:   main.c
 * Author: Sherry Chen
 *
 * Created on July 18, 2016, 12:11 PM
 * 
 * Version: 3.0
 * Description: 
 *      4 DC_motor integrated;
 *      4 break_beam integrated;  (modified value, without capacitor)
 *      B,N,S,W_counter, B_remain, B_SpacingTime
 *      ramp_servo, PIC-I2C-Arduino communicate
 *      NO continous servo
 *   RA0,1,5,4
 *      
 *      done message: delay time?

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
int N_remain = 0;
int S_remain = 0;
int W_remain = 0;

int B_spacingTime = 0;
int N_spacingTime = 0;
int S_spacingTime = 0;
int W_spacingTime = 0;

int B_done = 0;
int N_done = 0;
int S_done = 0;
int W_done = 0;



int max = 4;
unsigned short analog_result;
int i;

unsigned short readADC(char channel);

void motorStart_0();
void motorStop_0();
void motorStart_1();
void motorStop_1();
void motorStart_2();
void motorStop_2();
void motorStart_3();
void motorStop_3();
void i2cArduino(char char_to_arduino);




void servoRotate_clockwise();
void servoRotate_ConStop();
void servoRotate_counter();



void main(void) {

    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    OSCCON = 0xF2;  // Use 8 MHz internal oscillator block
    
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
    ADCON1 = 0x0B;  // RA0-3 are analog (pg. 222)
    ADCON2bits.ADFM = 1; // Right justify A/D result
    // </editor-fold>
    
    /* Initialize LCD. */
    
    //while(1){
        //motorStart_3();
        //motorStart_0();
    //}
    initLCD();  

    i2cArduino('2');
    while(1){
        
    }
    //i2cArduino('1');
    
            
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    
    /* Initialize LCD. */
    initLCD();                                             
    
            /******************* 0:bolts (screws)
             * motor_0: RC0
             * break_beam: ADC RA0
             
             ************/
    
    
    
    initLCD();
    printf("%d",B_counter);
    __delay_ms(50);
    motorStart_0();
    //}
    
    while (1){
       
        if (B_counter == max){       //max number
                motorStop_0();
                break;
        }
        __lcd_home();
       
       //printf("RA0: %.3x", readADC(0));
        if (readADC(0)<= 250 ){   //800      before caliberation: 32800
            //motorStart_0();  
            B_counter ++;
            initLCD();
            printf("%d", B_counter);
            __delay_ms(10);
            }
        //__delay_ms(60);           //nuts = 70 ms
       
    
       
    }
    initLCD();
    printf("done");
    __delay_ms(1000);
        
    
    
    /*********** 1:Nuts 
     * motor_1: RC1
     * readADC: RA1
     *************/
 
    
    initLCD();
    printf("%d",N_counter);
    __delay_ms(50);
    motorStart_1();
    
    while(1){
            
        if (N_counter == max){
                motorStop_1();
                break;
        }
        if (readADC(1)<=250 ){   //800
            //motorStart_0();  
            N_counter ++;
            initLCD();
            printf("%d", N_counter);
            __delay_ms(3);
            }
            
        }
    
    initLCD();
    printf("done");
    __delay_ms(1000);
    
    //continuous servo Rotate
    /*
    for (i = 0; i< 30; i ++){
        servoRotate_counter();
    }
    */
    
    
    //}
    /*********** 2: spacer 
     * motor_2: RC2
     * readADC : RA5
     
     *************/
    
    initLCD();
    printf("%d",S_counter);
    __delay_ms(50);
    motorStart_2();
    
    while(1){
            
        if (S_counter == max){
                motorStop_2();
                break;
        }
        if (readADC(5)<=150 ){   //800     RA2
            //motorStart_0();  
            S_counter ++;
            initLCD();
            printf("%d", S_counter);
            __delay_ms(50);
            }
            
        }
    
    initLCD();
    printf("done");
    __delay_ms(1000);
    
    
    //continuous servo Rotate
    /*
    for (i = 0; i< 30; i ++){
        void servoRotate_counter();
    }
    */
    
    
    /*********** 3: washer 
     * motor_3: RC5
     * readADC: RA4
     *************RC5*/
    initLCD();
    printf("%d",W_counter);
    __delay_ms(50);
    motorStart_3();
    
    while(1){
            
        if (W_counter == max){
                motorStop_3();
                break;
        }
        if (readADC(4)<=250 ){   //800
            //motorStart_0();  
            W_counter ++;
            initLCD();
            printf("%d", W_counter);
            __delay_ms(50);
            }
            
        }
    
    initLCD();
    printf("done");
    __delay_ms(1000);
    
    
    
    
   
    i2cArduino('2');
    
    
    
    
    initLCD();
    printf("Bolts:%d",B_counter);
    __delay_ms(100);
    
    initLCD();
    printf("Nuts:%d",N_counter);
    __delay_ms(100);
    
    initLCD();
    printf("Spacer:%d",S_counter);
    __delay_ms(100);
    
    initLCD();
    printf("Washers:%d",W_counter);
    __delay_ms(100);
    


    motorStart_0();
    motorStart_1();
    motorStart_2();
    motorStart_3();

    while(1){
        if (B_done == 1 && S_done == 1 && N_done == 1 && W_done ==1){
            break;
        }
        if (B_spacingTime>= 15000){
            motorStop_0();
            B_done = 1;
        }

        if (N_spacingTime>= 15000){
            motorStop_1();
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

        if (readADC(0)<=250 ){   //800
            //motorStart_0();  
            B_spacingTime=0;
            B_remain ++;
            initLCD();
            printf("%d", B_remain);
            //__delay_ms(10);
            }
        if (readADC(1)<=250 ){   //800
            //motorStart_0(); 
            N_spacingTime=0; 
            N_remain ++;
            initLCD();
            printf("%d", B_remain);
            //__delay_ms(10);
            }
        if (readADC(5)<=250 ){   //800
            //motorStart_0(); 
            S_spacingTime=0; 
            S_remain ++;
            initLCD();
            printf("%d", B_remain);
            //__delay_ms(10);
            }
        if (readADC(4)<=250 ){   //800
            //motorStart_0();  
            W_spacingTime=0;
            W_remain ++;
            initLCD();
            printf("%d", B_remain);
            //__delay_ms(30);
            }

        B_spacingTime+=200;
        N_spacingTime+=200;
        S_spacingTime+=200;
        W_spacingTime+=200;

    }
    
    while(1){
    initLCD();
    printf("remain Bolts:%d",B_remain);
    __delay_ms(100);
    
    initLCD();
    printf("remain Nuts:%d",N_remain);
    __delay_ms(100);
    
    initLCD();
    printf("remain Spacer:%d",S_remain);
    __delay_ms(100);
    
    initLCD();
    printf("remain Washers:%d",W_remain);
    __delay_ms(100);
    }
    
    
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
            
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('3'); // Write key press data
    I2C_Master_Stop(); 
        
}

void motorStop_0(){
            
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('4'); // Write key press data
    I2C_Master_Stop(); 
        
}

void motorStart_1(){
        I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('5'); // Write key press data
    I2C_Master_Stop(); 
}


void motorStop_1(){
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('6'); // Write key press data
    I2C_Master_Stop(); 
}



void motorStart_2(){
        I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('7'); // Write key press data
    I2C_Master_Stop(); 
}


void motorStop_2(){
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('8'); // Write key press data
    I2C_Master_Stop(); 
}

void motorStart_3(){
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('9'); // Write key press data
    I2C_Master_Stop(); 
}

void motorStop_3(){
        I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    
   
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('0'); // Write key press data
    I2C_Master_Stop(); 
}


/*
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

*/
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

void i2cArduino(char char_to_arduino){
     //I2C
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
    I2C_Master_Write(char_to_arduino); // Write key press data
    I2C_Master_Stop(); 
}