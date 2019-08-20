/* 
 * File:   DCmotor.h
 * Author: sherrychan
 *
 * Created on February 21, 2018, 12:51 PM
 */

#ifndef DCMOTOR_H
#define	DCMOTOR_H



#include <xc.h>
#include "configBits.h"



unsigned int angle = 0,i;
const char array[] = "01";
int white_tape = 0;                                                               //change to 0

/*
void motorStart_0();
void motorStop_0();


void motorStart_1();
void motorStop_1();


void motorStart_2();
void motorStop_2();


void motorStart_3();
void motorStop_3();

*/
void servoRotate_clockwise();
void servoRotate_ConStop();
void servoRotate_counter();


int read_IR();




#endif	/* DCMOTOR_H */

