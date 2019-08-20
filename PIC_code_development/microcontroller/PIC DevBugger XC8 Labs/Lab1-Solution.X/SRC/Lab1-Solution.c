#include <xc.h>               // Required CCI and device header file support
#include "LCD-XC.h"     // Required for LCD routines

int main(void)
{

    /*---------------------------------------------------------------------------
      Setup and write text to LCD to show program is working
    ---------------------------------------------------------------------------*/
    mOPEN_LCD;                     // Setup PMP and initialize LCD
    mLCD_CLEAR;                    // Clear Screen
#pragma warning push
#pragma warning disable 359
    LCDPutStr("Hello world!");     // Write text string to LCD
#pragma warning pop
    /*---------------------------------------------------------------------------
      Loop forever...
    ---------------------------------------------------------------------------*/
    while(1);
}
/********************************************************************************
|  CLASS:         Getting Started with MPLAB XC Compilers
|  PROGRAM:       Lab1.c   
|  AUTHOR:        Mark Reynolds
|  DATE:          Jan 2013
|  DESCRIPTION:   Used to test if project configuration is correct.
|                 No modification of this file is required to complete the lab.
|  REQUIREMENTS:  LCD driver must be included in the project
| 
|  REVISION HISTORY:
|  January 2013   Mark Reynolds  First Release
********************************************************************************/