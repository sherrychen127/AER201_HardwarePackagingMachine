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
int white_tape = 1;                                                             //change to 0


void motorStart_0();
void motorStop_0();


void motorStart_1();
void motorStop_1();


void motorStart_2();
void motorStop_2();


void motorStart_3();
void motorStop_3();


void servoRotate90();
void servoRotate0();
void servoRotate180();
void servoRotateCon();



void servoRotate90_2();
void servoRotate0_2();
void servoRotate180_2();
void servoRotateCon_2();

void servoRotate90_3();
void servoRotate0_3();
void servoRotate180_3();
void servoRotateCon_3();

void servoRotate90_4();
void servoRotate0_4();
void servoRotate180_4();
void servoRotateCon_4();


int find_handle();
int read_IR();




#endif	/* DCMOTOR_H */

