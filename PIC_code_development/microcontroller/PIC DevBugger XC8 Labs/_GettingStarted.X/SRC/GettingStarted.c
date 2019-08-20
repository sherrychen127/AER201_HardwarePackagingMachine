/*****************************************************************************

 Welcome to Getting Started with Microchip Live Online Classes!

 The purpose of this lab is to check that everything is installed and
 connected correctly for the class. There is nothing to write or change
 in the lab.  Simply follow the instructions below.
 If everything works you will see a password displayed on the LCD.
 This means your tools are properly installed and running.

 If you run into trouble double check that you have installed everything per
 the "Getting Started" instructions.  If you still have problems running this
 lab then please sign up for the Live Online class
 "TLS0000 Getting Started with Microchip Live Online" which can be found at
 www.microchip.com/training

 ******************************************************************************

 To run this lab:

 1) Double click on the MPLAB X icon on your desktop
 2) FILE -> OPEN Project C:\MTT\<class number>\Getting Started.X
 3) Select folder named GETTING STARTED.X
 4) Click on the OPEN PROJECT button in the lower corner of the dialog box.


To run this on the Proteus VSM[ISIS] Simulator, follow these steps:

 1) Select DEBUG -> DEBUG PROJECT(GETTING STARTED)
 2) The project will build and Proteus VSM[ISIS] will automatically open
 3) Wait for Proteus VSM[ISIS] to initialize (this may take a minute or so)
 4) Click DEBUG -> CONTINUE to start the simulation. Once the message Success is
    displayed on the LCD in the Proteus VSM[ISIS] Viewer window, then you have
    successfully installed and configured the tools needed to attend your class.

 5) Click DEBUG -> PAUSE to halt the simulation
 6) Close Proteus VSM[ISIS] by clicking the FILE -> EXIT from the Proteus VSM[ISIS] Menu
 7) Close the Getting Started project by clicking FILE -> CLOSE PROJECT(GETTING STARTED)
 8) Close MPLAB X by clicking FILE -> EXIT from the MPLAB X menu

  
If you have NOT installed the Proteus VSM[ISIS] Simulator, then follow these steps to
reconfigure the project to use the built in MPLAB X Simulator:

  1) Click FILE - PROJECT PROPERTIES(GETTING STARTED)
  2) On the right hand side of the configuration window that opens, select SIMULATOR, APPLY
  3) On the left hand side of the configuration window, click SIMULATOR
  4) Under the options categories pull down, select UART1 IO Options
  5) Check the box beside 'Enable UART1 IO' and ensure that Output is set to 'Window'
  6) Click OK.  You have now reconfigured the project for the MPLAB X Simulator

  7) Select DEBUG ->  DEBUG PROJECT(GETTING STARTED)
  8) The project will build and the MPLAB X Simulator will automatically start
  9) Wait for the MPLAB X Simulator to intialize (this may take a minute or so)
 10) Click DEBUG -> CONTINUE to start the simulation.
 11) Wait for the UART1 Output Window to appear, this may take as much as 30 seconds
     NOTE: This window is a sub-window of the Output window
 12) If a message is displayed in the UART1 Output Window, then you have succesfully
     installed and configured the tools needed to attend your class.

 13) Click DEBUG -> PAUSE to halt the simulation
 14) Close the Getting Started project by clicking FILE -> CLOSE PROJECT(GETTING STARTED)
 15) Close MPLAB X by clicking FILE -> EXIT from the MPLAB X menu

 ******************************************************************************/

//-------------------------------------------------- select PIC & configure

#include <xc.h>                                     // Processor Header file
#include <stdio.h>                                  // required for printf()
#include "USART-XC.h"                               // USART header file
#include "LCD-XC.h"                                 // LCD header file

//-------------------------------------------------- variables 

char  MyString[] = "Success";                       // Tools verification message

//-------------------------------------------------- code

int main(void)
{
    mOPEN_LCD;
    mLCD_CLEAR;
    LCDPutStr(MyString);                            // send to LCD

    mOPEN_USART;
    printf("\n\r%s",MyString);                      // send to USART

    while(1);
}


/**********************************************************************
  Stu Chandler     Mar 2013        v6.2 updates to USART and LCD routines
  Stu Chandler     Feb 2013        v6.1 USART now displays on Proteus virtual terminal (8 Bit)
                                        Removed lib files for ease of build with configurations
  Stu Chandler     Feb 2013        v6.0 added USART routines for all processors     
  Mark Reynolds    Feb 2013        v5.3 new LCD routines, introduced configurations
  Stu Chandler     Jan 2013        v5.0 restructured configs from .H to .C
  Stu Chandler     Oct 2012        v4.1 updated for XC compilers
  Stu Chandler     Apr 2012        v3.7 updated MPLAB X support
  Mark Reynolds    Feb 2012        v3.4 added support for MPLAB X
  Stu Chandler     Oct 2011        v3.0 added printf support for MPLAB SIM
  Stu Chandler     Oct 2011        v2.0 updated to 2011 tools
  Mark Reynolds    March 2011      v1.0 initial release
**********************************************************************/

/**********************************************************************
* © 2013 Microchip Technology Inc.
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Inc. (“Microchip”) licenses this software to you
* solely for use with Microchip dsPIC® digital signal controller
* products. The software is owned by Microchip and is protected under
* applicable copyright laws.  All rights reserved.
*
* SOFTWARE IS PROVIDED “AS IS.”  MICROCHIP EXPRESSLY DISCLAIMS ANY
* WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP
* BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
* DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
* PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
* BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
* ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
**********************************************************************/
