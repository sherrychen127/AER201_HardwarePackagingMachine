
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






/****servo_Rotate code*/

void servoRotate_clockwise(){
      //PORTB as output
    for (i = 0; i<1; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(1400); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(18600);
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
    for (i = 0; i<1; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(2000); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(18000);
    }
    //clockwise;
    
}












//servo turns while read IR

int read_IR(){
    while(1){
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





