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

//RB0 & RB1


void main()
{
  // PORT B as output port
 //PORTB = 1; // Set RB0 to high
 do
 {
   //To turn motor clockwise
   LATCbits.LATC2 = 1;  //RB0 HIGH
   TRISCbits.RC2 = 0;
   //LATAbits.LATA2 = 0;  //RB2 LOW
   __delay_ms(2000);//2 seconds delay

   //To Stop motor
   //LATAbits.LATA0 = 1;  //RB0 HIGH
   //LATAbits.LATA2 = 1; // RB2 LOW 
   //__delay_ms(2000);//2 seconds delay

   //To turn motor counterclockwise direction
   LATCbits.LATC2 = 1;  //RA0 HIGH
   //LATAbits.LATA2 = 1;
   //__delay_ms(2000);//2 seconds delay

   //To Stop motor
   //LATAbits.LATA0 = 0;  //RA0 HIGH
   //LATAbits.LATA2 = 0;
   __delay_ms(2000); // 2 seconds delay
   
   TRISC = 0;
   LATCbits.LATC2 = 0;
   __delay_ms(2000);
   TRISC = 0;

 }while(1);
}