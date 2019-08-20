#include <xc.h>
#include <stdio.h>
#include "USART-XC.h"

#if __XC8
   void USARTInit()
    {
        RX_PIN = 1;
        TX_PIN = 1;
        SPBRG = DIVIDER;                // 9600:0x0C  19200:0x18
        RCSTA = 0x90;                   // 8 bits/RCEN/CREN
        TXSTA = 0x24;                   // 8 bits/TXEN/ASYNC/BRGH
    }

    void putch(unsigned char byte)
    {
        while(!TXIF) continue;          // wait until TX register is empty
        TXREG = byte;                   // load TXREG with byte
        NOP();                          // wait one Tcyc
    }
#endif                                  // __XC8


#if __XC16
    void USARTInit()
    {
        #ifdef __PIC24FJ64GA004__
            #include <pps.h>
            IOMap();                    // remap UART pins for 24FJ64GA004
        #endif

        #ifndef __simulator
            __C30_UART=2;               // associate printf with UART2 for HW (default is UART1);
        #endif

        U2BRG = BRGVAL;
        U2MODEbits.UARTEN = 1;          // enable UART
        U2STAbits.UTXEN = 1;            // enable UART TX
    }

    void IOMap(void)
    {
        #ifdef __PIC24FJ64GA004__
            PPSUnLock;                  // Unlock Peripheral Pin Select configuration
            RPINR19bits.U2RXR = 19;     // Map RP19 pin to input function U2RX
            RPOR12bits.RP25R = 5;       // Map Output Function U2TX to RP25
            PPSLock;                    // Lock Peripheral Pin Select configuration
        #endif
        return;
    }
#endif                                  // __XC16


    
/*********************************************************************
* FileName:        USART-XC.c
* Processor:       PIC16 or PIC18 on PICDEM 2 plus
* Processor:       PIC24 on Explorer 16
* Compiler:        XC8 & XC16
* Company:         Microchip Technology, Inc.
* Version:         1.2
* Software License Agreement
*
* The software supplied herewith by Microchip Technology Incorporated
* (the “Company”) for its PICmicro® Microcontroller is intended and
* supplied to you, the Company’s customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
*
* Author            Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Stu Chandler      Mar 2013    v1.3 replaced __XCn__ with __XCn due to parser bug
* Mark Reynolds     Mar 2013    v1.2 updated for PIC24 VSM virtual terminal
* Stu Chandler      Feb 2013    v1.1 Modified to work with Proteus VSM virtual terminal
* Stu Chandler      Feb 2013    v1.0 First Release for XC8 & XC16
*********************************************************************
*
*   Provides USART setup routines required for printf() function in XC8.
*   XC16 compiler defaults to the USART settings that work for PIC24FJ128GA010
*   and PIC24FJ64GA004 therefore no USART setup is explicitly required for printf()
*   for these processors
*
*********************************************************************/