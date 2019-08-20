/*
 * File:   main.c
 * Author: sherrychan
 *
 * Created on February 20, 2018, 11:32 AM
 */
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "I2C.h"

int B_count = 0;
int N_count = 0;
int S_count = 0;
int W_count = 0;






unsigned short readADC(char channel);
void I2C_init();
void I2C_sendData(unsigned char char_data);
void interrupt interruptHandler(void);
        

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    //OSCCON = 0xE2;  // Use 8 MHz internal oscillator block  //0xF2   
    //oscillator initialize
    
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS1 = 1;
    OSCTUNEbits.PLLEN = 1;     //uncomment
    /********************************* PIN I/O ********************************/
    /* Write outputs to LATx, read inputs from PORTx. Here, all latches (LATx)
     * are being cleared (set low) to ensure a controlled start-up state. */  
    LATA = 0x00;
    LATB = 0x00; 
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;

    /* After the states of LATx are known, the data direction registers, TRISx
     * are configured. 0 --> output; 1 --> input. Default is  1. */
    TRISA = 0xFF; // All inputs (this is the default, but is explicated here for learning purposes)
    TRISB = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00; // All output mode on port D for the LCD
    TRISE = 0x00;
    
    /************************** A/D Converter Module **************************/
    ADCON0 = 0x00;  // Disable ADC
    ADCON1 = 0b00001111; // Set all A/D ports to digital (pg. 222)
    ADCON2bits.ADFM = 1;

    // </editor-fold>
    
    
    ei(); // Enable all interrupts
    initLCD();
    I2C_init();//Initialize I2C Master with 100 kHz clock. 
    
    

    
    LATCbits.LATC0 = 1;  //set RC0 HIGH-> disable KPD
    TRISCbits.RC0 = 0;
    

    RBIE = 1;  //set RBIE port B to interrupt on change
    
    
    //dispense washer
    
    //printf("B_count:%d",B_count);
    //B_count = 0;
    initLCD();
    
    I2C_sendData('5'); //start motor
    
    while(1){
        TRISBbits.RB5 = 1; // set data direction for RA0 to input (i.e. 1)
        int input = PORTBbits.RB5;
        initLCD();
        //printf("%d",input);
        printf("%d",B_count);
        /*
        printf("Bcount:%d",B_count);
        if(B_count >= 4){
            I2C_sendData('6');   //stop motor
            break;
        }
        __lcd_home();
        */
    }
    initLCD();
    RBIE = 0; 
    //finish
    while(1){
        
        printf("B_count:%d",B_count);
        __lcd_home();
    }

    initLCD();    
}
    
   



void interrupt interruptHandler(void){
    /* This function is mapped to the interrupt vector, and so is called when
     * any interrupt occurs to handle it. Note that if any interrupt is enabled,
     * and it does not have a handler to clear it, then unexpected behavior will
     * occur, perhaps even causing the PIC to reset.
     *
     * Arguments: none
     * 
     * Returns: none
     */
    
    
    if (RBIF){
        
        
        //printf("B_count:%d",B_count);
        
        //RB4: bolts
      
        
        TRISBbits.RB5 = 1; // set data direction for RA0 to input (i.e. 1)
        int input = PORTBbits.RB5;
        
        if (input == 0){
            initLCD();
            B_count++;
            //printf("%d",input);
            printf("%d",B_count);
            __lcd_home();
        }
       
        
        
        
        /*
        if (readADC(11)<= 250){
            
            B_count++;
            initLCD();
            //printf("RB11: %.3x", readADC(11));
            printf("B_count:%d",B_count);
            __lcd_home();
        }*/

        RBIF = 0;
        return;
    }
}






unsigned short readADC(char channel){
    /* Reads the analog input from the specified analog channel.
     *
     * Arguments: channel, the byte corresponding to the channel to read
     *
     * Returns: the 10-bit value corresponding to the voltage read from
     *          the specified channel
     */
    
    ADCON0 = (channel & 0x0F) << 2; // Select ADC channel (i.e. pin)
    ADON = 1; // Enable module
    ADCON0bits.GO = 1; // Initiate sampling
    while(ADCON0bits.GO_NOT_DONE){  continue;   } // Poll for acquisition completion
    return (ADRESH << 8) | ADRESL; // Return result as a 16-bit value
}


void I2C_init(){
    I2C_Master_Init(100000);          //change to 80000
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Stop();
}
void I2C_sendData(unsigned char char_data){
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b00010000); // 7-bit Arduino slave address + write
    I2C_Master_Write(char_data); // rotate servo and find C0
    I2C_Master_Stop();
}

