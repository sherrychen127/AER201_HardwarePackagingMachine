#include <xc.h>
#include "LCD-XC.h"

char a, b;
char c;
////////////////////////////////////////////////////////////////////////////////
// Exercise 6.2
//     Add a function prototype for the assemble functions
//     _incFunction (char parameter)
//     _decFunction (char parameter)
////////////////////////////////////////////////////////////////////////////////
char incFunction(char x);  // _incFunction (char parameter)
char decFunction(char x);   //_decFunction (char parameter)

int main(void)
{
    LCDInit();
    a = 5;
    b = 3;
    ////////////////////////////////////////////////////////////////////////////////
    // Exercise 6.3:
    //     Call _incFunction; store result in c
    ////////////////////////////////////////////////////////////////////////////////
    c = incFunction(a);             // ### Call _incFunction.

    LCDPutChar(c+0x30);             // Display value of c on first line of LCD
    LCDPutCmd (LCD_CURSOR_LINE2);   // Move cursor to second line of LCD

    ////////////////////////////////////////////////////////////////////////////////
    // Exercise 6.4:
    //     Call _decFunction ;
    //     and store the result in c
    ////////////////////////////////////////////////////////////////////////////////
    c = decFunction(b);             // ### Task (6.4): Call _decFunction
                                    // ### and store the result in c

    LCDPutChar(c+0x30);             // Display value of c on second line of LCD

    while (1);
}



/********************************************************************************
|  CLASS:         Getting Started with MPLAB XC
|  AUTHOR:        Mark Reynolds
|  DATE:          June 2013
|  DESCRIPTION:   Mixing C and assembly.
|  REQUIREMENTS:
|
|  REVISION HISTORY:
|  Jun 2013       Mark Reynolds created for XC8 v1.20

********************************************************************************/