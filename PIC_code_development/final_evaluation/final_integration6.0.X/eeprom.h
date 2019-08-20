/* 
 * File:   eeprom.h
 * Author: sherrychan
 *
 * Created on April 7, 2018, 11:43 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "configBits.h"

char ReadEEByte (char address);
unsigned char WriteEEByte (char address, char data);
void writeAndInc (char * address, char data);
char readAndInc (char * address);
void writeEntry (unsigned char * quantityInputs, unsigned char setInputs [8][4], unsigned short int * numRemaining, unsigned short int operationTime, unsigned char * timeEnd, char numStored);
void saveResults (unsigned char * quantityInputs, unsigned char setInputs [8][4], unsigned short int * numRemaining, unsigned short int operationTime, unsigned char * timeEnd);
char retrieveResults (unsigned char * quantityInputs, unsigned char setInputs [8][4], unsigned short int * numRemaining, unsigned short int * operationTime, unsigned char * timeEnd, unsigned char logOption);





#endif	/* EEPROM_H */

