/*
 * File:   main.c
 * Author: Tyler Gamvrelis
 * 
 * Created on August 13, 2017, 6:00 PM
 * 
 * Description: Demonstration of GLCD initialization, and the fundamental
 *              graphics "function", drawing rectangles. Drawing pixels are also
 *              demonstrated as a special case of drawing rectangles.
 * 
 * Preconditions:
 *   1. GLCD is in a PIC socket
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "GLCD_PIC.h"

void drawTeamName();

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /********************************* PIN I/O ********************************/
    /* Write outputs to LATx, read inputs from PORTx. Here, all latches (LATx)
     * are being cleared (set low) to ensure a controlled start-up state. */  
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS1 = 1;
    OSCTUNEbits.PLLEN = 1; 
    
    LATA = 0x00;
    LATB = 0x00; 
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;

    /* After the states of LATx are known, the data direction registers, TRISx
     * are configured. 0 --> output; 1 --> input. Default is  1. */
    TRISA = 0xFF; // All inputs (this is the default, but is explicated here for learning purposes)
    TRISB = 0xFF;
    TRISC = 0b10000000; /* RC3 is SCK/SCL (SPI/I2C),
                         * RC4 is SDA (I2C),
                         * RC5 is SDA (SPI),
                         * RC6 and RC7 are UART TX and RX, respectively. */
    TRISD = 0b00000001; /* RD0 is the GLCD chip select (tri-stated so that it's
                         * pulled up by default),
                         * RD1 is the GLCD register select,
                         * RD2 is the character LCD RS,
                         * RD3 is the character LCD enable (E),
                         * RD4-RD7 are character LCD data lines. */
    TRISE = 0b00000100; /* RE2 is the SD card chip select (tri-stated so that
                         * it's pulled up by default).
                         * Note that the upper 4 bits of TRISE are special 
                         * control registers. Do not write to them unless you 
                         * read §9.6 in the datasheet */
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    // </editor-fold>
    
    /* Initialize GLCD. */
    initGLCD();
    
    /* Declare local variables. */
    unsigned char rotation = 0, x = 0, y = 0;
    glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, WHITE);
    /* Main loop. */
    while(1){
        /* Fill screen with red. */
        
        
        drawTeamName();
        __delay_ms(1000);


        /* Fill screen with rainbow colors. */
        /*
        glcdDrawRectangle(0, 18, 0, GLCD_SIZE_VERT, RED);
        glcdDrawRectangle(18, 36, 0, GLCD_SIZE_VERT, ORANGE);
        glcdDrawRectangle(36, 54, 0, GLCD_SIZE_VERT, YELLOW);
        glcdDrawRectangle(54, 72, 0, GLCD_SIZE_VERT, GREEN);
        glcdDrawRectangle(72, 90, 0, GLCD_SIZE_VERT, BLUE);
        glcdDrawRectangle(90, 108, 0, GLCD_SIZE_VERT, INDIGO);
        glcdDrawRectangle(108, 128, 0, GLCD_SIZE_VERT, VIOLET);
        */
        
        /* Demonstrate inversion. */
        /*
        __delay_ms(500);
        __INVON(); // Turn on color inversion
        __delay_ms(500);
        __INVOFF(); // Turn off color inversion
        __delay_ms(500);
        */
        /* Draw white in the four corners pixels. */
        /*
        glcdDrawPixel(0, 0, WHITE);
        __delay_ms(500);
        glcdDrawPixel(GLCD_SIZE_HORZ, 0, WHITE);
        __delay_ms(500);
        glcdDrawPixel(GLCD_SIZE_HORZ, GLCD_SIZE_VERT, WHITE);
        __delay_ms(500);
        glcdDrawPixel(0, GLCD_SIZE_VERT, WHITE);
        __delay_ms(500);
        */
        /* Place 128 pixels in accordance with some arbitrarily-chosen math. */
        /*
        for(x = 0; x < GLCD_SIZE_HORZ; x++){
            if(x % (GLCD_SIZE_VERT/16) == 0){
                glcdDrawPixel(GLCD_SIZE_VERT - (x * 8), (x % 3) * 33, x * 2048);
            }
            else{
                glcdDrawPixel(x, GLCD_SIZE_VERT - x, x * 2048);
            }
            __delay_ms(10);
        }
        */
        /* Fill screen with blue/pink pattern, pixel-by-pixel. */
        /*
        for(y = 0; y < GLCD_SIZE_VERT; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, x*y*16);
            }
        }
        */
        
        /* Fill screen with blue pattern, pixel-by-pixel. */
        /*
        for(y = 0; y < GLCD_SIZE_VERT; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, (x+8)*(y+8));
            }
        }
        */
        /* Fill screen with green, pixel-by-pixel. Note the difference in speed
         * when using this method and when using the first method 
         * (glcdDrawRectangle). The first method is faster because we only have
         * to define the drawing window once, as the entire screen. The method
         * below re-defines the drawing window once per iteration, so
         * 128 * 128 = 16, 384 times. Thus, it is slower for filling the screen.
         * */
        /*
        for(y = 0; y < GLCD_SIZE_VERT; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, GREEN);
            }
        }
        */
        
        /* Fill screen with black, and then demonstrate the pixel-by-pixel
         * addressing by drawing 5 lines slowly in white. The pixel-by-pixel
         * drawing is slower here intentionally so that you can see that each
         * pixel is indeed being addressed separately. */
        /*
        glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, BLACK);
        for(y = 0; y < 5; y++){
            for(x = 0; x < GLCD_SIZE_HORZ; x++){
                glcdDrawPixel(x, y, WHITE);
                __delay_ms(5);
            }
        }
        */
        
        /* Rotate display at the end of each iteration. */
        /*
        switch(rotation % 4){
            case 0:
                glcdSetOrigin(ORIGIN_TOP_RIGHT);
                break;
            case 1:
                glcdSetOrigin(ORIGIN_BOTTOM_RIGHT);
                break;
            case 2:
                glcdSetOrigin(ORIGIN_BOTTOM_LEFT);
                break;
            case 3:
                glcdSetOrigin(ORIGIN_TOP_LEFT);
                break;
        }
        rotation++;
        */
    }
}


void drawTeamName(){
    //glcdDrawRectangle(0, GLCD_SIZE_HORZ, 0, GLCD_SIZE_VERT, WHITE);
    //T
    glcdDrawRectangle(5*4, 11*4, 9*4, 11*4, BLACK);
    glcdDrawRectangle(8*4, 9*4, 11*4, 16*4, BLACK);
    //3
    glcdDrawRectangle(12*4, 17*4, 9*4, 11*4, BLACK);
    glcdDrawRectangle(16*4, 17*4, 11*4, 16*4, BLACK);
    glcdDrawRectangle(12*4, 16*4, 12*4, 13*4, BLACK);
    glcdDrawRectangle(12*4, 16*4, 14*4, 16*4, BLACK);
    //4
    glcdDrawRectangle(18*4, 19*4, 9*4, 14*4, BLACK);
    glcdDrawRectangle(19*4, 23*4, 12*4, 14*4, BLACK);
    glcdDrawRectangle(21*4, 22*4, 9*4, 16*4, BLACK);

    //heat
    glcdDrawRectangle(24*4, 25*4, 10*4, 13*4, RED);
    glcdDrawRectangle(25*4, 27*4, 9*4, 14*4, RED);
    glcdDrawRectangle(27*4, 28*4, 10*4, 15*4, RED);

    glcdDrawRectangle(28*4, 30*4, 9*4, 14*4, RED);
    glcdDrawRectangle(30*4, 31*4, 10*4, 13*4, RED);

}

void drawBolt(){
    
}

void drawWasher(){
    glcdDrawRectangle(14*4, 5*4, 20*4, 5*4, BLACK);
}