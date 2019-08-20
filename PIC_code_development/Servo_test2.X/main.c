//#define _XTAL_FREQ 32000000

#include <xc.h>
#include "configBits.h"

//calculate the on-time duration for 1degree angular displacement
//create delay function to calculate time duration
//

unsigned int angle = 0, i;
int counter_test = 0;

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

void servoRotate180() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD1 = 1;
    TRISDbits.RD1 = 0;
    __delay_us(4000);
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(16000);
  }
}



void servoRotate_n180() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD1 = 1;
    TRISDbits.RD1 = 0;
    __delay_us(1800);
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(18200);
  }
}



void servoRotate_stop(){
    unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(1500);
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(17500);
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


void servoRotateCon(){
    for(i=0;i<1;i++)
    {
        LATDbits.LATD1 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(2000); // pulse of 1500us
        LATDbits.LATD1 = 0;
        TRISDbits.RD1 = 0;
        __delay_us(18000);
    }
}



/*servo_2 ****************
 ***************************/

//SG90

void servoRotate180_2() //180 Degree
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


void servoRotate0_2(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD2 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(1500); // pulse of 800us
        LATDbits.LATD2 = 0;
        TRISDbits.RD2 = 0;
        __delay_us(18500);
    }
    //TRIS = 0;
    
}

void servoRotate90_2(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD2 = 1;
        TRISDbits.RD2 = 0;
        __delay_us(1000); // pulse of 1500us
        LATDbits.LATD2 = 0;
        TRISDbits.RD2 = 0;
        __delay_us(19000);
    }
}


void servoRotateCon_2(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD2 = 1;
        TRISDbits.RD2 = 0;
        __delay_us(14000); // pulse of 1500us
        LATDbits.LATD2 = 0;
        TRISDbits.RD2 = 0;
        __delay_us(6000);
    }
}





/*servo_3 ****************
 ***************************/



void servoRotate180_3() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD3 = 1;
    TRISDbits.RD3 = 0;
    __delay_us(2200);
    LATDbits.LATD3 = 0;
    TRISDbits.RD3 = 0;
    __delay_us(17800);
  }
}


void servoRotate0_3(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD3 = 1;
        TRISDbits.RD3 = 0;
        __delay_us(800); // pulse of 800us
        LATDbits.LATD3 = 0;
        TRISDbits.RD3 = 0;
        __delay_us(19200);
    }
    //TRIS = 0;
    
}

void servoRotate90_3(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD3 = 1;
        TRISDbits.RD3 = 0;
        __delay_us(1500); // pulse of 1500us
        LATDbits.LATD3 = 0;
        TRISDbits.RD3 = 0;
        __delay_us(18500);
    }
}


void servoRotateCon_3(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD3 = 1;
        TRISDbits.RD3 = 0;
        __delay_us(14000); // pulse of 1500us
        LATDbits.LATD3 = 0;
        TRISDbits.RD3 = 0;
        __delay_us(6000);
    }
}





/***********servo_4 ****************
 ***********************************/



void servoRotate180_4() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD4 = 1;
    TRISDbits.RD4 = 0;
    __delay_us(2200);
    LATDbits.LATD4 = 0;
    TRISDbits.RD4 = 0;
    __delay_us(17800);
  }
}


void servoRotate0_4(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD4 = 1;
        TRISDbits.RD4 = 0;
        __delay_us(800); // pulse of 800us
        LATDbits.LATD4 = 0;
        TRISDbits.RD4 = 0;
        __delay_us(19200);
    }
    //TRIS = 0;
    
}

void servoRotate90_4(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD4 = 1;
        TRISDbits.RD4 = 0;
        __delay_us(1500); // pulse of 1500us
        LATDbits.LATD4 = 0;
        TRISDbits.RD4 = 0;
        __delay_us(18500);
    }
}


void servoRotateCon_4(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD4 = 1;
        TRISDbits.RD4 = 0;
        __delay_us(14000); // pulse of 1500us
        LATDbits.LATD4 = 0;
        TRISDbits.RD4 = 0;
        __delay_us(6000);
    }
}



void main(){
     //PORT B as output Port
    //servoRotate0();
    //while(1){
        
    //    servoRotate90();
    //    __delay_ms(1000);
        //servoRotate0();
        //__delay_ms(500);
    
    //while(1){
    //for (int i = 0; i<68; i ++){    // coninuous servo one round
    //servoRotate0_2();
    __delay_ms(1000);
    servoRotate90_2();
    __delay_ms(1000);
    servoRotate180_2();
    __delay_ms(1000);
    //}
    //}
        //servoRotateCon();
        //__delay_ms(1000);
    //}
    
    
    
    
    //while(1){
    //    servoRotate_stop();
    //}
    
        
        
        //__delay_ms(1000);
        //servoRotate_stop();
        //__delay_ms(500);
        //servoRotate180();
        //counter_test++;
        //printf("%d",counter_test);
        //__delay_ms(100);
        //__lcd_home();
        //if (counter_test == 54){
            
        //    break;
        //}
       //servoRotate_stop();
    //}
    //servoRotate_stop();
}