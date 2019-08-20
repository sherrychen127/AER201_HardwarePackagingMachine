
#include <xc.h>
//#include <stdio.h>
#include "configBits.h"
//#include "lcd.h"
//#include "I2C.h"

#define _XTAL_FREQ 32000000




#define switch1 PORTAbits.RA0 //



void main(void) {
    
   //TRISAbits.TRISA0 = 1;//RA0 input for taking input from IR
   //TRISD = 0x00; //output
  //TRISB = 0x00;
   //int switch_1 = PORTAbits.RA0; 
   
    //CMCON = 0x07; // Disable Comparator
    //ADCON1bits.PCFG0 = 1; // These 4 settings below determines the analog or digital input
    //ADCON1bits.PCFG1 = 1; // In our case we are making all the pins digital
    //ADCON1bits.PCFG2 = 1; // by setting them as 1111
    //ADCON1bits.PCFG3 = 1; // Check with the datasheet for a nice desc of these bits and config.
    //ADCON0bits.ADON = 0; // Disabled ADC
    TRISAbits.TRISA0 = 1; 
    while(1){
        /* Initialize local variables. */
        //unsigned char i = 0;
        //unsigned char temp = 0x00;
        if (switch1 == 1){
            LATA = 
        }
        temp = 1 << 7; // Set temporary byte to 0b10000000.
        /* Write temp to the latch, then bit shift to right. Iterate over the port
         * size. */
        for (i = 0; i < 8; i++){
            LATA = temp;
            temp >>= 1;
            __delay_ms(1000);
        }
        LATA = 0x00; 
    }
}
   
   
   
   
   //Servo Motor
   //while(1){
      //PORTBbits.RB1 == 1
   //   TRISBbits.RB0 = 1;
   //   int input = PORTBbits.RB1;
   //   if (input == 1){
          //_delay(350);
   //       LATBbits.LATB1 = 0;
   //       TRISBbits.RB1 = 0;
   //   }
   //   else{
   //       LATBbits.LATB1 = 1;
   //       TRISBbits.RB1 = 0;
   //   }
   //   _delay(3500);
      
  //}
    
//}

