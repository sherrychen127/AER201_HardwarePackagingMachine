/* 
 * File:   keypad.h
 * Author: sherrychan
 *
 * Created on February 21, 2018, 1:31 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include <xc.h>
#include <stdio.h>
#include "configBits.h"
#include <string.h>



int mode = 2;   //overall modes of operation of the machine
int change_mode = 0;   //variable that change mode=0 to mode=1

int operation = 0;  //final mode, variable for ISR
int operation_done = 0; //variable for interrupt(when = 1. mode = 0 restart)


//count gears
int gear_counter = 0;
int prev= 0;
int init_position = 5;                                                          //relative position to C0.  (calibrate)
int compartment_pos = 0;   //compartment position (C0,C1,C2....)


//
int operationTime = 0;     //actural run time for the machine


const char keys[] = "123A456B789C*0#D"; 
int fastener[100];
int state = 0;
char temp;
int assembly_step = 0;
int counter = 0; //useless
int counter_step = 0; //keep track of how many fastener_set + number displayed


int error = 0;//useless
int valid = 0;
int number = 0; //number of fasteners set
int total_number; //total number of fasteners per set




int prev_state;
int B=0,N=0,S=0,W=0;
const char strs[20][5] = {"B","N","S","W","BN","BS","BW","BBN","BBS","BBW","BNW",
                           "BSW","BWW","BNWW","BSWW","BBSW","BBNW","BNNW",
                            "BNNN","BWWW"};


char current_set[5];
char current_set2[5];
char temp_set[5];
char final_set[8][5];
int final_number[8];

char prev_set[8][5];
int prev_number[8];


int B_counter= 0;   //keep track of the dispensed fasteners;
int S_counter= 0;
int N_counter= 0;
int W_counter= 0;


int B_remain = 0;
int N_remain = 0;
int S_remain = 0;
int W_remain = 0;

int B_spacingTime = 0;
int N_spacingTime = 0;
int S_spacingTime = 0;
int W_spacingTime = 0;

int B_done = 0;
int N_done = 0;
int S_done = 0;
int W_done = 0;


int B_max = 4; //arbitrary max number for nuts
int N_max = 4;
int S_max = 4;
int W_max = 4;

char openHandle_data;
char nuts_data; 


unsigned char rotate_gear = '0';
unsigned char rotate_1compartment = '1';
unsigned char B_dispense = '2';
unsigned char N_dispense = '3';
unsigned char S_dispense = '4';

unsigned char motorStart_0 = '5';
unsigned char motorStop_0 = '6';

unsigned char motorStart_1 = '7';
unsigned char motorStop_1 = '8';

unsigned char motorStart_2 = '9';   //
unsigned char motorStop_2 = 10;

unsigned char motorStart_3 = 11;
unsigned char motorStop_3 = 12;

unsigned char servo_ramp = 13;
unsigned char close_handle = 14;








int compartment_array[8] = {0,1,0,1,0,1,0,1};   //which C is to be dispensed, index = compartment number {0,1,0,1,0,1,0,1};
int compartment_number[8] = {0,0,0,0,0,0,0,0}; //store the compartment number(index))

int B_array[8] = {0,1,0,1,0,3,0,0};                                               //change that!
int S_array[8] = {0,1,0,1,0,1,0,0}; 
int N_array[8]= {0,2,0,1,0,0,0,3};
int W_array[8]= {0,0,0,0,0,0,0,0};


//int white_tape = 0;     (include in the DCmotor.c file)
//int max = 5;
//int motor_counter=0; useless?
//int counter_test = 0; //useless(testing purposes))




int check();
int is_valid();
void generate_compartment_array(int step);

unsigned short readADC(char channel);

void store_prev();
void initialize();


#endif	/* KEYPAD_H */

