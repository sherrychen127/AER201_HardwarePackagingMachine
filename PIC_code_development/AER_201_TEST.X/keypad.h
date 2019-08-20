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


int B_count= 0;   //keep track of the dispensed fasteners;
int S_count= 0;
int N_count= 0;
int W_count= 0;



int compartment_array[8] = {0,0,0,0,0,0,0,0};   //which C is to be dispensed, index = compartment number 
int compartment_number[8] = {0,0,0,0,0,0,0,0}; //store the compartment number(index))

int B_array[8] = {0,0,0,0,0,0,0,0};                                               //change that!
int S_array[8] = {0,0,0,0,0,0,0,0}; 
int N_array[8]= {0,0,0,0,0,0,0,0};
int W_array[8]= {0,0,0,0,0,0,0,0};






int check();
int is_valid();
void generate_compartment_array(int step);

unsigned short readADC(char channel);

void store_prev();
void initialize();


#endif	/* KEYPAD_H */

