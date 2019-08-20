
#include "DCmotor.h"

/*******************************************************************************
 * 4 motors interface (RC0,RC1,RC2,RC3)
 * 4 servos interface (RD1,RD2,RD3,RD4)
 * IR sensor interface (RA4)
 * PR sensor interface  (read ADC) (AN2)
 * 
 
 
 ******************************************************************************/







/*****motor interface******/

//motor_0
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

//motor_1

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












/*******servo interface*********/


void servoRotate180() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD1 = 1;
    TRISDbits.RD1 = 0;
    __delay_us(2200);
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(17800);
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
    for(i=0;i<50;i++)
    {
        LATDbits.LATD1 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(14000); // pulse of 1500us
        LATDbits.LATD1 = 0;
        TRISDbits.RD1 = 0;
        __delay_us(6000);
    }
}

/*servo_2 ****************
 ***************************/

void servoRotate180_2() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    LATDbits.LATD2 = 1;
    TRISDbits.RD2 = 0;
    __delay_us(2200);
    LATDbits.LATD2 = 0;
    TRISDbits.RD2 = 0;
    __delay_us(17800);
  }
}

void servoRotate0_2(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD2 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(800); // pulse of 800us
        LATDbits.LATD2 = 0;
        TRISDbits.RD2 = 0;
        __delay_us(19200);
    }
}

void servoRotate90_2(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD2 = 1;
        TRISDbits.RD2 = 0;
        __delay_us(1500); // pulse of 1500us
        LATDbits.LATD2 = 0;
        TRISDbits.RD2 = 0;
        __delay_us(18500);
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


/**********PR sensor Interface************/






//servo turns while finding handle
int find_handle(){
    return 1;
}



//servo turns while read IR

int read_IR(){
    while(1){
        
        servoRotate180();
        __delay_ms(200);
        servoRotate0();
        __delay_ms(200);
        TRISAbits.RA4 = 1; //RA0
        unsigned char input = PORTAbits.RA4;
        //printf("input:");
        //putch(array[input]);
        //__delay_ms(500);
        //__lcd_home();
        if (array[input] == '1'){
            white_tape = 1;
            return 1;
        }
        else{
            return 0;
        }
        
    }
}
