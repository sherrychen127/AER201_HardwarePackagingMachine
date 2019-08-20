#include <xc.h>
#include <stdio.h>
#include "configBits.c"
#include "LCD-XC.h"

void LCDInit()
{  
    LCD_PORT = 0x00;                   // clear latches before enabling TRIS bits
    TRISD = 0x00;

    __delay_ms(LCD_Startup);        // required by display controller to allow power to stabilize
    LCDPutCmd(0x32);                // required by display initialization
    LCDPutCmd(FUNCTION_SET);        // set interface size, # of lines and font
    LCDPutCmd(DISPLAY_SETUP);       // turn on display and sets up cursor
    mLCD_CLEAR;
    LCDPutCmd(ENTRY_MODE);          // set cursor movement direction
}

/*******************************************************************
* FUNCTION:     LCDWriteNibble()
* INPUTS:       data byte to be written to display
*               bit for writing to commnd or data register
* OUTPUTS:      None
* DESCRIPTION:  Fuction to write a nibble
* AUTHOR:       Mark Reynolds
* DATE:         Jan 2013
* REVISIONS:    Jan 2013 - Initial Version
 * 
* Michael Ding          12/2016         Updated for PIC18f4620 DevBugger 4
 * 
*******************************************************************/
void LCDWriteNibble(unsigned char ch,unsigned char b)
{
    ch = ch & 0xF0;                 // mask off the nibble to be transmitted

    LCD_PORT = LCD_PORT & 0x0F;     // clear the top half of LCD_PORT
    LCD_PORT = LCD_PORT | ch;       // move the nibble onto LCD_PORT

    LCD_RS = b;                     // set data/instr bit to 0 = insructions; 1 = data
    LCD_EN = 1;                     // set up enable before writing nibble
    LCD_EN = 0;                     // turn off enable after write of nibble
}

/*******************************************************************
* FUNCTION:     LCDPutChar()
* INPUTS:       ch = character to send
* OUTPUTS:      None
* DESCRIPTION:  Writes character to LCD at current cursor position
* AUTHOR:       Mark Reynolds
* DATE:         Jan 2013
* REVISIONS:    Jan 2013 - Initial Version
 * 
* Michael Ding          12/2016         Updated for PIC18f4620 DevBugger 4
 * 
*******************************************************************/
void LCDPutChar(unsigned char ch)
{
    __delay_ms(LCD_delay);
    LCDWriteNibble(ch,data);
    ch = ch << 4;
    LCDWriteNibble(ch,data);
}

/*******************************************************************
* FUNCTION:     LCDPutCmd()
* INPUTS:       ch = character to send
* OUTPUTS:      None
* DESCRIPTION:  Writes character to LCD command register
* AUTHOR:       Mark Reynolds
* DATE:         Jan 2013
* REVISIONS:    Jan 2013 - Initial Version
 * 
* Michael Ding          12/2016         Updated for PIC18f4620 DevBugger 4
 * 
*******************************************************************/
void LCDPutCmd(unsigned char ch)
{
    __delay_ms(LCD_delay);
    LCDWriteNibble(ch,instr);
    ch = ch << 4;
    __delay_ms(1);      
    LCDWriteNibble(ch,instr);
}

/*******************************************************************
* FUNCTION:     LCDPutStr()
* INPUTS:       *ptr = Pointer to string to send
* OUTPUTS:      None
* DESCRIPTION:  Writes string to LCD at current cursor position
* AUTHOR:       Mark Reynolds
* DATE:         Jan 2013
* REVISIONS:    Jan 2013 - Initial Version
*******************************************************************/
void LCDPutStr(unsigned char *ptr)
{
    while(*ptr) LCDPutChar(*(ptr++));
}


/*********************************************************************
* FileName:        LCD-XC.c
* Dependencies:    See INCLUDES section below
* Processor:       PIC18 on DevBugger 4
* Compiler:        xc8 
* Company:         Microchip Technology, Inc.
* Version:         1.1
* Software License Agreement
*
* The software supplied herewith by Microchip Technology Incorporated
* (the �Company�) for its PICmicro� Microcontroller is intended and
* supplied to you, the Company�s customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
*
* Author            Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Mark Reynolds	    Mar 2013    v1.2 added missing macros for backward compatibility
* Mark Reynolds     Feb 2013    v1.1 First Release for XC8 & XC16; Supports PICDEM2 & Explorer 16
* Mark Reynolds     Jan 2013    v1.0 First release for xc8; PICDEM2 standard driver
 * 
* Michael Ding          12/2016         Updated for PIC18f4620 DevBugger 4
 * 
********************************************************************************/