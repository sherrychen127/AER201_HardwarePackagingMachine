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


int B_input = 1;
int N_input = 1;
int S_input = 1;
int W_input = 1;




unsigned short readADC(char channel);
void I2C_init();
void I2C_sendData(unsigned char char_data);
void interrupt interruptHandler(void);
        

void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    OSCCON = 0xE2;  // Use 8 MHz internal oscillator block  //0xF2   
    //oscillator initialize
    /*
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
     */ 
    OSCTUNEbits.PLLEN = 1;
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
    

    //RBIE = 1;  //set RBIE port B to interrupt on change
    
    //dispense 
    printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    initLCD();
    

    
    I2C_sendData('5'); //start motorStart_0: bolts
     while(1){
         /*
        TRISBbits.RB5 = 1; // set data direction
        B_input = PORTBbits.RB5;   //bolts
          */ 
         initLCD();
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        __lcd_home();
        //bolts
          
         
        if (B_count>=4){
            I2C_sendData('6');   //stop motor bolts
            //break;
        }
        
        if (readADC(0)<=250){
            B_count ++;
        }
        __delay_ms(10);
     }
    
              
    
    I2C_sendData('7');  //start motorStart_1: nuts
    while(1){
        /*
        TRISBbits.RB4 = 1; // set data direction
        N_input = PORTBbits.RB4;   //nuts
        initLCD();
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        __lcd_home();
        //nuts
         */
        if (N_count>=4){
            I2C_sendData('8');   //stop motor bolts
            break;
        }
        if (readADC(1)<=250){
            N_count++;
        }
        
        
    }
    
    
    I2C_sendData('9');  //Start motorStart_2: Spacer
    while(1){
        TRISBbits.RB6 = 1; // set data direction 
        S_input = PORTBbits.RB6;  //spacer
        initLCD();
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        __lcd_home();
        if (S_count>=4){
            I2C_sendData(12);   //stop motor bolts
            break;
        }
        
        if (S_input ==0){
            S_count ++;
        }
    }
    
    
    
    I2C_sendData(11);   //Start motorStart_3: washers
    
    while(1){
        TRISBbits.RB7 = 1; // set data direction 
        W_input = PORTBbits.RB7;  //washer
        initLCD();
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        __lcd_home();
        if (W_count>=4){
            I2C_sendData(12);   //stop motor bolts
            break;
        }
        if (W_input == 0){
            W_count++;
        }
    }
    
        
        
        //nuts
        //if (N_count>=4){
        //    I2C_sendData('8');   //stop motor bolts
        //    //break;
        //}
        
        //if (S_count>=4){
        //    I2C_sendData(10);   //stop motor bolts
        //    //break;
        //}
        
        //if (W_count>=4){
        //    I2C_sendData(12);   //stop motor bolts
        //    //break;
        //}
        
        //if (B_count>=4 && N_count>=4&& S_count>=4&& W_count>=4){
        //    break;
        //}
        
        //initLCD();
        //__lcd_home();
        //printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        //__lcd_home();
        
        /*
        printf("Bcount:%d",B_count);
        if(B_count >= 4){
            I2C_sendData('6');   //stop motor
            break;
        }
        __lcd_home();
        */
    
    initLCD();
    RBIE = 0; 
    //finish
    while(1){
        
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
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
      
        
        TRISBbits.RB5 = 1; // set data direction
        B_input = PORTBbits.RB5;   //bolts
        
        TRISBbits.RB4 = 1; // set data direction
        N_input = PORTBbits.RB4;   //nuts
        
        TRISBbits.RB6 = 1; // set data direction 
        S_input = PORTBbits.RB6;  //spacer
        
        TRISBbits.RB7 = 1; // set data direction 
        W_input = PORTBbits.RB7;  //washer
        
        
        
        if (B_input == 0){
            //initLCD();
            B_count++;
            //printf("%d",B_count);
            //__lcd_home();
        }
        
        
        if (N_input == 0){
            N_count++;
        }
        
        if (S_input == 0){
            //initLCD();
            S_count++;
            //printf("%d",S_count);
            //__lcd_home();
        }
        
        if (W_input == 0){
            //initLCD();
            W_count++;
            //printf("%d",W_count);
            //__lcd_home();
        }
      
        initLCD();
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        __lcd_home();
        

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

