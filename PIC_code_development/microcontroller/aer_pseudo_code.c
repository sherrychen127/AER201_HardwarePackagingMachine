/* created by: Yuxuan Chen

 * pin assignment:

 * Photoresistance sensor
 * IR sensor
 * Motor: 4 (rotate reservoirs)
 * servo motor: 1 (rotate the box)
 * Servo: 2 (rotate the ramp)

 */

#include <stdio.h>
#include <stdlib.h>
#include <includes.h>
#include "configbits.h"
#include "keypadInterrupt.c"

#include <adc.h>        //A/D conversion functions
#include <delays.h>




int bolt_array[8];  //how many bolt per compartment
int spacer_array[8]; 
int nut_array[8];
int washer_array[8];
int compartment[8];

const int angle = 45;

//keep track of the number of fasteners after been dispensed
int bolt_counter = 0;
int spacer_counter = 0;
int nut_counter = 0;
int washer_counter = 0;

int main_counter = 0;


void main(){
	int operation_mode = 1;   
	//mode = 1: standby; 
	//mode = 2: detecting; 
	//mode = 3: dispensing

	// mode = 4: rotate
	// mode = 5: DONE!!!
	
	if (operation_mode == 1){
		keypadInterrupt();
		operation_mode == 2;
	}
	
	else if (operation_mode ==2){
		servo_motor_start();
		if (IR_sensor_module() ==1){
			servo_motor_stop();
			delay(5000);
			operation_mode = 3;
		}
	}

	else if (operation_mode == 3){
		motor_start(1);
		motor_start(2);
		motor_start(3);
		motor_start(4);

		if (photoresistor(1,B)==1){
			bolt_counter++;
		};
		if (photoresistor(2,N) == 1){
			nut_number++;
		}
		if (photoresistor(2,N) == 1){
			spacer_number++;
		}
		if (photoresistor(2,N) == 1){
			washer_number++;
		}
		

		if (bolt_counter >= bolt_array[main_counter]){
				//bolt_counter
				//while(1){
					motor_stop(1);
					if (done = 1){
						operation_mode = 3;
					}
				}
				
			}
			if (Spacer_counter >= Spacer_array[main_counter]){
				//while(1){
					motor_stop(2);
				//	if (done = 1){
				//		break;
				//	}
				//}
			}
			if (nut_counter >= nut_array[main_counter]){
				//while(1){
					motor_stop(3);
				//	if (done = 1){
				//		break;
				//	}
				//}
			}
			if (washer_counter >= bolt_array[main_counter]){
				//while(1){
					motor_stop(4);
				//	if (done = 1){
				//		break;
				//	}
				//}
			}

			//if (washer_counter >= bolt_array[main_counter]&&)

			operation_mode = 4;

		}

	

			



			


		else if (operation_mode = 4){
			servo_motor_turn(angle*compartment[main_counter]);

			
			int bolt_max = sum(bolt_array);
			int nut_max = sum(nut_array);
			int spacer_max = sum(spacer_array);
			int washer_max = sum(washer_array);

			if (bolt_counter == bolt_max&&){
				operation_mode = 4;
			}



		}

		else if (operation_mode == 4){
			close_lid();
			initLCD();
			display_RTC();
			display_compete_message();
		}




		
		//else{
		//	servo_motor_start();
		//}
	



keypadInterrupt(){
	//see the keypad interface!
	operation_mode = 2;
}


//photoresistor

void photoresistor(int pr_number,int a){
	//set the pin for pr_number
	if value > 25{
		a++;
		return;
	}
}


//IR_sensor_module
int IR_sensor_module()
{
    int IR_value;
    
    OpenADC(ADC_FOSC_RC & ADC_RIGHT_JUST & ADC_8_TAD, ADC_CH7 &
            ADC_INT_OFF, 15);
    Delay10TCYx( 5 );    //Delay for 50TCY
    ConvertADC();        //Start Conversion
    while(BusyADC());    //Wait for ADC to finish
    IR_value = ReadADC();    //Read Result
    CloseADC();            //Disable the A/D converter

    return IR_value;
}




//motor 


void motor_start(int motor_number){
	//start rotating the motor

} 

void motor_stop(int motor_number){
	//stop the rotation of motor
}

void init_IO(){
	TRISAbits.TRISA6 = 1;
    TRISAbits.TRISA7 = 1;
    TRISGbits.TRISG12 = 0;
    TRISGbits.TRISB13 = 0;
    LATGbits.LATB12 = 0;
    LATGbits.LATB13 = 0;
    return;
}

void InitializeTimers(){
    // Initialize Timer1
    T1CON = 0x0000; // Set Timer1 Control to zeros
    T1CONbits.TCKPS=3; // prescale by 256
    T1CONbits.ON = 1; // Turn on Timer
    PR1= 0xFFFF; // Period of Timer1 to be full
    TMR1 = 0; // Initialize Timer1 to zero
    // Initialize Timer2
    T2CON = 0;
    T2CONbits.TCKPS = 7; // prescale by 256
    T2CONbits.T32 = 1; // use 32 bits timer
    T2CONbits.ON = 1;
    PR2 = 0xFFFFFFFF; // Period is set for 32 bits
    TMR2 = 0;
}



//servo_motor

int servo_motor_start(){
	//start the servo_motor
}



void close_lid(){
	motor_start();
	delay(200);
	motor_stop;
}

