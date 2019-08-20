

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"

/***** Constants *****/
const char keys[] = "123A456B789C*0#D"; 
const char array[] = "10";
int i;
int white_tape = 1;
int analog_result;
int counter = 0;
int max = 4;


/********
 if IR = 1: servo rotate
 * test if counter = 4
 
 */

void servoRotate90();
void servoRotate180();
void servoRotate0();
unsigned short readADC(char channel);


void main() {
    
    // <editor-fold defaultstate="collapsed" desc="Machine Configuration">
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
    // </editor-fold>
    
    INT1IE = 1; // Enable RB1 (keypad data available) interrupt
    ei(); // Enable all interrupts
    
    /* Initialize LCD. */
    initLCD();
    while(1){
        TRISAbits.RA4 = 1; //RA0
        unsigned char input = PORTAbits.RA4;
        putch(array[input]);
        __delay_ms(100);
        __lcd_home();
        //printf("input:");
        if (white_tape == 0){
            if (array[input]=='1'){
            white_tape = 1;
            //servoRotate90();
            __delay_ms(200);
            //servoRotate180();
            //__delay_ms(200);
            }
        }
        
        //else{
        //    servoRotate0();
            //__delay_ms(200);
        //}
        else if (white_tape == 1){
            //printf("%d",white_tape);
            
            //__delay_ms(200);
            //__lcd_home();
            //initLCD();
            
            if (counter>=max){
                initLCD();
                printf("your done");
                __delay_ms(200);
                __lcd_home();
            }
                
                //servoRotate180();
                //__delay_ms(200);
                //servoRotate0();
                //__delay_ms(200);
                
            else{
                printf("%d",counter);
                __delay_ms(200);
                __lcd_home();
        
       /* Print results to character LCD. Since ADC results are 10 bits, they
        * are split up into two registers ADRESH and ADRESL. The results of the
        * ADC are displayed in hexadecimal so that the values in each of these
        * registers will be easily visible; ADRESL corresponds to the two least
        * significant digits, while ADRESH corresponds to the most significant 
        * bit. */
       
                if (readADC(2)>32760){       // original circuit = 150
            
                    counter++;
                    //initLCD();
                    printf("%d",counter);
                    __delay_ms(100);
                    __lcd_home();
                }
            }   
            
                
        }
            //servoRotate90();
            //__delay_ms(200);
            //servoRotate180();
            
        
        
        
        //putch(array[input]);
        
        //__delay_ms(100);
        //__lcd_home();
        
    }
    
    
}


void servoRotate180(){ //180 Degree
  for(i=0;i<50;i++)
  {
    LATDbits.LATD1 = 1;
    TRISDbits.RD1 = 0;
    __delay_us(2200);
    LATDbits.LATD1 = 0;
    TRISDbits.RD1 = 0;
    __delay_us(17800);
  }
}

void servoRotate0(){
      //PORTB as output
    for (i = 0; i<50; i++){
        LATDbits.LATD1 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(800); // pulse of 800us
        LATDbits.LATD1 = 0;
        TRISDbits.RD1 = 0;
        __delay_us(19200);
    }
    //TRIS = 0;
    
}


void servoRotate90(){
    for(i=0;i<50;i++)
    {
        LATDbits.LATD1 = 1;
        TRISDbits.RD1 = 0;
        __delay_us(1500); // pulse of 1500us
        LATDbits.LATD1 = 0;
        TRISDbits.RD1 = 0;
        __delay_us(18500);
    }
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
    
    if(INT1IF){
        /* Interrupt on change handler for RB1. */
        
        /* Write key press data to bottom line of LCD. */
        __lcd_newline();
        unsigned char keypress = (PORTB & 0xF0) >> 4;
        putch(keys[keypress]);
        __lcd_home();
        
        INT1IF = 0;  // Clear interrupt flag bit to signify it's been handled
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
