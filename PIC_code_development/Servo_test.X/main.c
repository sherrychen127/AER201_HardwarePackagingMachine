//#define _XTAL_FREQ 32000000

#include <xc.h>
#include "configBits.h"
// BEGIN CONFIG
//#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
//#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
//#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
//#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
//#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
//#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
//#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG


//calculate the on-time duration for 1degree angular displacement
//create delay function to calculate time duration
//

unsigned int angle = 0, i;


//void servoRotate0() //0 Degree/
//{
//  unsigned int i;
//  for(i=0;i<50;i++)
//  {
//    RB0 = 1;
//    __delay_ms(800);
//    RB0 = 0;
//    __delay_ms(19200);
//  }
//}

//void servoRotate90() //90 Degree
//{
//  unsigned int i;
//  for(i=0;i<50;i++)
//  {
//    RB0 = 1;
//    __delay_ms(1500);
//    RB0 = 0;
//    __delay_ms(18500);
//  }
//}

//void servoRotate180() //180 Degree
//{
//  unsigned int i;
//  for(i=0;i<50;i++)
//  {
//    RB0 = 1;
//    __delay_ms(2200);
//    RB0 = 0;
//    __delay_ms(17800);
//  }
//}

//void main()
//{
//  TRISB = 0; // PORTB as Ouput Port
//  do
//  {
//    servoRotate0(); //0 Degree
//    __delay_ms(2000);
//    servoRotate90(); //90 Degree
//    __delay_ms(2000);
//    servoRotate180(); //180 Degree
//  }while(1);
//}
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


void main(){
     //PORT B as output Port
    while(1){
        
        //servoRotate90();
        //__delay_ms(500);
        servoRotate_clockwise();    
    }
}