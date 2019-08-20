/*
 * File:   main.c
 * Author: Sherry Chen
 *
 * version: 2.0
 * 
 *
 *  Description:
 *          ADC, motor, IR sensor integration.
 * 
 * Preconditions:
 *   1. Jumpers JP5 and JP4 are shorted
 *   2. Character LCD is in a PIC socket
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"

/**** Local function prototypes *****/
unsigned short readADC(char channel);

void servoRotate0();
void servoRotate90();
void servoRotate180();

void motorStart_0();  //fastener
void motorStop_0();    //reservoir
void motorStart_1();
void motorStop_1();

int i;


int counter = 0;
int counter_2 = 0;

int mode = 0;
int white_tape = 0;
int max = 7;
const char array[] = "10";

int compartment_array[8] = {0,1,0,1,0,1,0,1};
int B_array[8] = {0,3,0,2,0,1,0,4};




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
    initLCD();
    
    //while(1){
        motorStart_0();
        __delay_ms(2000);
        
        
    //}
    if (white_tape == 0){
        INT1IE = 1; // Enable RB1 (keypad data available) interrupt
        ei(); // Enable all interrupts
    
        /* Initialize LCD. */
        initLCD();
        while(1){
            TRISAbits.RA4 = 1; //RA0
            unsigned char input = PORTAbits.RA4;
            printf("IR reading:");
            putch(array[input]);
            __delay_ms(100);
            __lcd_home();
            //printf("input:");
            if (white_tape == 0){
                if (array[input]=='1'){
                white_tape = 1;
                //servoRotate90();
                __delay_ms(200);
                break;
                //servoRotate180();
                //__delay_ms(200);
                }
            }
            
        }
    }
    
    
    if (white_tape == 1){
        motorStop_0();
        printf("IR reading:%d",1);
        __delay_ms(600);
        __lcd_home();
        for (i = 0; i<8; i++) {
            motorStart_0();
            //__delay_ms(300);
            //motorStop_0();
            if (compartment_array[i] == 1){
                motorStop_1();
                initLCD();
                printf("C%d:",i);
                __delay_ms(700);
                //__lcd_home();
                while (counter <= B_array[i]){
                    motorStop_0();        //fastener
                    motorStart_1();      //reservoir
                    //__delay_ms(300);
                    if (readADC(2)<250){       // original circuit = 150
                        
                        initLCD();
                        counter++;
                        //initLCD();
                        printf("B:%d",counter);
                        __delay_ms(300);
                        __lcd_home();
                        
                    }
                }
                
                motorStop_1();
                
                initLCD();
                printf("done");
                __lcd_newline();
                printf("B:%d",counter);
                        
                __delay_ms(300);
                __lcd_home();
                counter = 0;
                
            }
            
            else{
                
                motorStart_0();
                motorStop_1();
                initLCD();
                printf("C%d:",i);
                //__delay_ms(300);
                printf("done");
                __delay_ms(2000);
                __lcd_home();
            }
                
        }
        initLCD();
        printf("all done");
        motorStop_0();
        __delay_ms(800);
        __lcd_home();
        
        counter = 0;
        
        printf("remain:%d",counter);
        __delay_ms(800);
        //motorStop_0()
        motorStart_1();
        servoRotate0();
        __delay_ms(200);
        servoRotate180();
        //__delay_ms(800);
        while(1){
            if (readADC(2)<250){
            counter++;
            printf("remain:%d",counter);
            __delay_ms(500);
            __lcd_home();
            }
            if (readADC(2)>=250){
                counter_2 ++;
                if (counter_2>=40){
                    break;
                }
            }
                
            
        }
        
        
        
    }
        motorStop_0();
        printf("done");
        __delay_ms(3000);
        
        
    /* Main loop. */
    
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
    return (ADRESH << 8) | ADRESL; // Return result as a 16-bit value
}

void servoRotate180() //180 Degree
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

void servoRotate_stop(){
    unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(2000);
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(18000);
  }
}





void servoRotate0(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD1 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(800); // pulse of 800us
        LATDbits.LATD1 = 0;
        TRISDbits.RD1 = 0;
        __delay_us(19200);
    }
    //TRIS = 0;
    
}

void servoRotate90(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD1 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(1500); // pulse of 1500us
        LATDbits.LATD1 = 0;
        TRISDbits.RD1 = 0;
        __delay_us(18500);
    }
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

