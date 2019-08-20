/*
 * File:   main.c
 * Author: Sherry Chen
 *
 * tested on march 20, worked
 * 
 * 
 * Description: 
 *      4 DC_motor integrated;
 *      4 break_beam integrated;  (modified value, without capacitor)
 *      B,N,S,W_counter, B_remain
 *      ramp_servo
 *      NO continous servo

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


int W_counter = 0;
int W_remain = 0;
int W_spacingTime = 0;

int max = 4;
unsigned short analog_result;

unsigned char I2Cdata; 
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
    TRISC = 0x00; /* RC3 is SCK/SCL (SPI/I2C),
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
    initLCD();  
    
    
    
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    
    
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
            
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('1'); // Write key press data
    I2C_Master_Stop();
    
 
    
    /*********** 3:washers 
     * motor_1: D9
     * readADC: RA3
     *************/
 
    
    initLCD();
    printf("%d",W_counter);
    __delay_ms(100);
    motorStart_3();
    //while(1){
    //    printf("RA1: %.3x", readADC(1));
    //    __lcd_home();
    //    __delay_ms(100);
    //}
    ///*
    
    while(1){
        
        if (W_counter >= max){
            W_counter = 0;
            motorStop_3();
                //break;
        }
        
        I2C_Master_Start();
        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
        I2Cdata = I2C_Master_Read(NACK); // Read one char only
        I2C_Master_Stop();
        initLCD();
        if (I2Cdata == 'a'){
            W_counter ++;
            I2Cdata = 'b';
            printf("%d",W_counter);
            __lcd_home();
                
        }
        else{
            printf("%d",W_counter);
        }
        
        
        
          
    }
    //*/
    
    initLCD();
    printf("done");
    __delay_ms(800);
    

    // arduino rotate microservo
    //I2C
    I2C_Master_Init(100000); 
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
    

            
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write('2'); // Write key press data
    I2C_Master_Stop();
    

    initLCD();
    motorStart_3();
    
    W_spacingTime = 0;
    initLCD();
    printf("%d", W_remain);
    while (1){

        if (W_spacingTime >= 30000){ //15sec
            motorStop_3();
            break;
        }
        
        I2C_Master_Start();
        I2C_Master_Write(0b00010001); // 7-bit Arduino slave address + Read
        I2Cdata = I2C_Master_Read(NACK); // Read one char only
        I2C_Master_Stop();
        initLCD();
        if (I2Cdata == 'a'){
            W_remain ++;
            I2Cdata = 'b';

                
        }
        else{

        }
        __lcd_home();
        printf("%d",W_remain);
        

   
        __lcd_newline();
        printf("%d",W_spacingTime);
        
        __lcd_home();

        W_spacingTime +=200;
    
        
    }
    
    
    
    while(1){
    initLCD();
    printf("remain Washers:%d",W_remain);
    __delay_ms(1000);
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

