#ifndef __USART_XC_H__
#define __USART_XC_H__

void USARTInit(void);                // manual USART init required for printf() with XC compilers
#define mOPEN_USART USARTInit();

#if __XC8
    #if _18F4620
        #define BAUD 19200           // Proteus virtual terminal expects 19200/n/1
    #else
        #define BAUD 9600            // Proteus virtual terminal expects 9600/n/1
    #endif

    #define FOSC 10000000L
    #define DIVIDER ((int)(FOSC/(16UL * BAUD) -1))

    #define RX_PIN TRISC7
    #define TX_PIN TRISC6
#endif                               // __XC8


#endif                               // __USART_XC_H__
