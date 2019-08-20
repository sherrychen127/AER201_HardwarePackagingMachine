/*
 * File:   main.c
 * Author: Sherry
 * version: 1.0
 * 
 * 
 * Description: 
 *         DC motors rotate: four reservoirs, B,N,S,W
 *         B: motor_stop0(): C0      ADC: RA0
 *         N: motor_stop1(): C
 *         S:
 *         W:
 * 
 *      DC motor_spin
 *      break_beam sensor
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"

/**** Local function prototypes *****/

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




void servoRotate80();
void servoRotate0();

void servoRotate80_2();
void servoRotate0_2();

void servoRotate80_3();
void servoRotate0_3();

void servoRotate80_4();
void servoRotate0_4();



void servoRotate_clockwise();
void servoRotate_ConStop();
void servoRotate_counter();




void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
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
    TRISC = 0x00;
    TRISD = 0x00; // All output mode on port D for the LCD
    TRISE = 0x00;

    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0x0B;  // RA0-3 are analog (pg. 222)
    ADCON2bits.ADFM = 1; // Right justify A/D result
    //</editor-fold>
    
    /* Initialize character LCD. */
    
    
    //ADCON0 =  0b0000;
   
    
    //ADCON1 = 0x10;
    //while(1){
    //servoRotate_stop();
    //while(1){
    motorStart_0();
    //}
    
    
    
    
    
    /******************* bolts (screws)************/
    initLCD();
    printf("%d",B_counter);
    __delay_ms(100);
    motorStart_0();
    //}
    
    while (1){
        //motorStart_0();
        if (B_counter == max){
                motorStop_0();
                break;
        }
        if (readADC(0)<=250 ){   //800
            //motorStart_0();  
            B_counter ++;
            initLCD();
            printf("%d", B_counter);
            __delay_ms(50);
            }
        //__delay_ms(60);           //nuts = 70 ms
       
    
       
    }
    initLCD();
    printf("done");
    __delay_ms(1000);
        
    //servoRotate0();
    for (i = 0; i< 30; i ++){
        servoRotate_counter();
    }
    
    
    /*********** Nuts *************/
    //if (state == 0){
    
    initLCD();
    printf("%d",N_counter);
    __delay_ms(100);
    motorStart_1();
    
    while(1){
            
        if (N_counter == max){
                motorStop_1();
                break;
        }
        if (readADC(2)<=250 ){   //800
            //motorStart_0();  
            N_counter ++;
            initLCD();
            printf("%d", N_counter);
            __delay_ms(50);
            }
            
        }
    
    initLCD();
    printf("done");
    __delay_ms(1000);
    
    //continuous servo Rotate
    
    for (i = 0; i< 30; i ++){
        servoRotate_counter();
    }
    
    
    //}
    /*********** spacer *************/
    
    initLCD();
    printf("%d",S_counter);
    __delay_ms(100);
    motorStart_2();
    
    while(1){
            
        if (S_counter == max){
                motorStop_2();
                break;
        }
        if (readADC(2)<=250 ){   //800
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
    
    for (i = 0; i< 30; i ++){
        void servoRotate_counter();
    }
    
    
    
    /*********** washer *************/
    initLCD();
    printf("%d",W_counter);
    __delay_ms(100);
    motorStart_3();
    
    while(1){
            
        if (W_counter == max){
                motorStop_3();
                break;
        }
        if (readADC(3)<=250 ){   //800
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
    
    


 
    motorStart_0();
        while (1){
        //motorStart_0();
        if (B_remain == 2){
                motorStop_0();
                break;
        }
        if (readADC(0)<=250 ){   //800
            //motorStart_0();  
            B_remain ++;
            initLCD();
            printf("%d", B_remain);
            __delay_ms(50);
            }
        //__delay_ms(60);           //nuts = 70 ms
       
    
       
    
        
    }
    
    
    
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
    
    initLCD();
    printf("remain bolt:%d",W_counter);
    __delay_ms(1000);
    initLCD();
    printf("remain spacer:%d",W_counter);
    __delay_ms(1000);
    initLCD();
    printf("remain nuts:%d",W_counter);
    __delay_ms(1000);initLCD();
    printf("remain Washers:%d",W_counter);
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
    
        LATCbits.LATC3 = 1;  //RC0 HIGH
        TRISCbits.RC3 = 0;
        //LATAbits.LATA2 = 0;  //RC2 LOW
        __delay_ms(200);//2 seconds delay
    
}

void motorStop_3(){
    LATCbits.LATC3 = 0;  //RC0 LOW
    TRISCbits.RC3 = 0;
    //LATAbits.LATA2 = 0;  //RC2 LOW
    __delay_ms(200);//2 seconds delay
}





// servos




void servoRotate0()
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD1 = 1;
    TRISDbits.RD1 = 0;
    __delay_us(2000);
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(18000);
  }
}





void servoRotate80(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD1 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(1500); // pulse of 800us
        LATDbits.LATD1 = 0;
        TRISDbits.RD1 = 0;
        __delay_us(18500);
    }
    //TRIS = 0;
    
}



/*servo_2 ****************
 ***************************/


void servoRotate0_2() // 
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD2 = 1;
    TRISDbits.RD2 = 0;
    __delay_us(2000);
    LATDbits.LATD2 = 0;
    TRISDbits.RD2 = 0;
    __delay_us(18000);
  }
}

void servoRotate80_2(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD2 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(1500); // pulse of 800us
        LATDbits.LATD2 = 0;
        TRISDbits.RD2 = 0;
        __delay_us(18500);
    }
}



/*servo_3 ****************
 ***************************/
void servoRotate0_3() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD3 = 1;
    TRISDbits.RD3 = 0;
    __delay_us(2000);
    LATDbits.LATD3 = 0;
    TRISDbits.RD3 = 0;
    __delay_us(18000);
  }
}

void servoRotate80_3(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD3 = 1;
        TRISDbits.RD3 = 0;
        __delay_us(1500); // pulse of 800us
        LATDbits.LATD3 = 0;
        TRISDbits.RD3 = 0;
        __delay_us(18500);
    }    
}




/***********servo_4 ****************
 ***********************************/
void servoRotate0_4() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD4 = 1;
    TRISDbits.RD4 = 0;
    __delay_us(2000);
    LATDbits.LATD4 = 0;
    TRISDbits.RD4 = 0;
    __delay_us(18000);
  }
}

void servoRotate80_4(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD4 = 1;
        TRISDbits.RD4 = 0;
        __delay_us(1500); // pulse of 800us
        LATDbits.LATD4 = 0;
        TRISDbits.RD4 = 0;
        __delay_us(18500);
    }
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

//motor

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