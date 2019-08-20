/*
 * File:   main.c
 * Author: sherrychan
 *  integrate four reservoirs, and run in sequence according to fasteners array
 * Created on February 20, 2018, 11:32 AM
 */
#include <xc.h>
#include "configBits.h"
#include "lcd.h"
#include "I2C.h"

int compartment_array[8] = {0,1,0,1,0,1,0,1};   //which C is to be dispensed, index = compartment number {0,1,0,1,0,1,0,1};


int B_array[8] = {0,2,0,2,0,1,0,1};                                               //change that!
int S_array[8] = {0,1,0,2,0,3,0,1}; 
int N_array[8]= {0,3,0,1,0,2,0,2};
int W_array[8]= {0,2,0,1,0,3,0,1};


int B_count = 0;
int N_count = 0;
int S_count = 0;
int W_count = 0;


int B_input = 0;
int N_input = 0;
int S_input = 0;
int W_input = 0;

int B_spacingTime = 0;
int N_spacingTime = 0;
int S_spacingTime = 0;
int W_spacingTime = 0;

int spacingTime = 4000;    //5000 (8-9 sec)    4000 (6-7 sec)

int max = 4;

unsigned short readADC(char channel);
void I2C_init();
void I2C_sendData(unsigned char char_data);
void interrupt interruptHandler(void);
        
void Bolt_dispense(int B_max);
void Nut_dispense(int N_max);
void Spacer_dispense(int S_max);
void Washer_dispense(int W_max);

void Bolt_remain(int time);
void Nut_remain(int time);
void Spacer_remain(int time);
void Washer_remain(int time);


void main(void) {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    //OSCCON = 0xF2;  // Use 8 MHz internal oscillator block  //0xF2   
    //oscillator initialize
    
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.SCS1 = 1;
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

    RBIE = 1;  //set RBIE port B to interrupt on change
    
    //dispense 
    printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    initLCD(); 
    
    TRISBbits.RB5 = 1; // bolt
    TRISBbits.RB7 = 1; // washer
    TRISBbits.RB6 = 1; // spacers
    TRISBbits.RB4 = 1; // nuts
    
    for (int i = 0; i< 8; i++){
        initLCD();
        printf("processing C%d",i);
        __delay_ms(80);
        if (compartment_array[i] == 1){
            B_count = 0;
            N_count = 0;
            S_count = 0;
            W_count = 0;
            Bolt_dispense(B_array[i]);
            Nut_dispense(N_array[i]);
            Spacer_dispense(S_array[i]);
            Washer_dispense(W_array[i]);
        }
        
    }
      
    
    
    
    __delay_ms(300);
    
    Bolt_remain(spacingTime);
    Nut_remain(spacingTime);
    Spacer_remain(spacingTime);
    Washer_remain(spacingTime);
    
    
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

        B_input = PORTBbits.RB5;   //bolts     
        N_input = PORTBbits.RB6;   //nuts
        S_input = PORTBbits.RB4;  //spacer
        W_input = PORTBbits.RB7;  //washer
        
        
        
        if (B_input == 1){
            B_spacingTime = 0;
            initLCD();
            printf("bolt_interrupt");
            __lcd_home();
            B_count++;
            
        }
        
        
        if (N_input == 1){
            N_spacingTime = 0;
            initLCD();
            printf("nut_interrupt");
            __lcd_home();
            N_count++;
        }
        
        if (S_input == 1){
            S_spacingTime = 0;
            S_count++;
            initLCD();
            
            printf("spacer_interrupted");
            __lcd_home();
        }
        
        if (W_input == 1){
            W_spacingTime = 0;
            initLCD();
            printf("washer_interrupt");
            __lcd_home();
            W_count++;
            //printf("%d",W_count);
            //__lcd_home();
        }
        initLCD();
        printf("interrupted");
        __lcd_home();
        //initLCD();
        //printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
        //__lcd_home();
        

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

void Bolt_dispense(int B_max){
    //dispense bolt
    I2C_sendData('5'); // rotate bolt motor
    while(1){
        initLCD();
        __lcd_home();
        if (B_count >= B_max){
            I2C_sendData('6');
            break;
        }
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
}

void Nut_dispense(int N_max){
    I2C_sendData('7');
    N_count = 0;
    while(1){
        initLCD();
        __lcd_home();
        if (N_count >= N_max){
            I2C_sendData('8');
            break;
        }
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
    
}

void Spacer_dispense(int S_max){
    I2C_sendData('9');
    S_count = 0;
    while(1){
        initLCD();
        __lcd_home();
        if (S_count >= S_max){
            I2C_sendData(10);
            break;
        }
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
    
}

void Washer_dispense(int W_max){
    I2C_sendData(11);
    W_count = 0;
    while(1){
        initLCD();
        __lcd_home();
        if (W_count >= W_max){
            I2C_sendData(12);
            break;
        }
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
    
}



void Bolt_remain(int time){
    I2C_sendData('5'); // rotate bolt motor
    while(1){
        initLCD();
        __lcd_home();
        if (B_spacingTime >= time){
            I2C_sendData('6');
            break;
        }
        B_spacingTime +=100;
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
}


void Nut_remain(int time){
    I2C_sendData('7'); // rotate bolt motor
    while(1){
        initLCD();
        __lcd_home();
        if (N_spacingTime >= time){
            I2C_sendData('8');
            break;
        }
        N_spacingTime +=100;
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
}


void Spacer_remain(int time){
    I2C_sendData('9'); // rotate bolt motor
    while(1){
        initLCD();
        __lcd_home();
        if (S_spacingTime >= time){
            I2C_sendData(10);
            break;
        }
        S_spacingTime +=100;
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
}


void Washer_remain(int time){
    I2C_sendData(11); // rotate bolt motor
    while(1){
        initLCD();
        __lcd_home();
        if (W_spacingTime >= time){
            I2C_sendData(12);
            break;
        }
        W_spacingTime +=100;
        printf("B:%d,N:%d,S:%d,W:%d",B_count,N_count,S_count,W_count);
    }
}