/*
 * File:   main.c
 * Author: Sherry Chen
 * version: 2.0
 * 
 * break_beam connect to RA3. 
 * 
 * Description: 
 *      IR_sensor detects white tape
 *      servo Rotate according to B_array[8]
 * 
 * Preconditions:
 * (ADC module)
 *   1. Jumpers JP5 and JP4 are shorted
 *   2. Character LCD is in a PIC socket
 */

/***** Includes *****/
#include <xc.h>
#include "configBits.h"
#include "lcd.h"

// gear stuff
int compartment = 0;   //compartment number
int counter = 0; //count gear_teeth
int init_position = 5;       
const unsigned int gear_breakbeam_size = 1;
int gear_breakbeam[1];
int gear_bb_reading();
void initialize_gear_breakbeam_history();

int prev = 0;
int i;


const char array[] = "01";
int white_tape = 1;                                                             //change to 0

int B_array[8] = {1,1,1,1,1,1,1,1};     

unsigned short readADC(char channel);
void servoRotate_clockwise();
void servoRotate_ConStop();
void servoRotate_counter();
void count_gear();       //increment counter

int read_IR();



void main(void) {
// <editor-fold defaultstate="collapsed" desc="Machine Configuration">
    /******************************* OSCILLATOR *******************************/
    OSCCON = 0xF2;  // Use 8 MHz internal oscillator block
    
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
    ADCON1 = 0x0B;  // RA0-3 are analog (pg. 222)
    ADCON2bits.ADFM = 1; // Right justify A/D result
    //</editor-fold>
    
    initLCD();
    initialize_gear_breakbeam_history();
    //rotate 360+ degrees, to open the handle
    
    while(1){
        if (counter>= 50){
            counter = 0;    //initialize the counter
            break;
        }
        servoRotate_clockwise();
        count_gear();           //counter++, init_position remains the same
        printf("gear:%d",counter);         
        //__delay_ms(50);
        __lcd_home();
    }
    
    //stop when white tape detected. manually measure the distance between white tape 
    while(1){
        
        servoRotate_clockwise();
        count_gear();           //counter++, init_position ++ when white_tape detected
        printf("gear:%d",counter);         
        //__delay_ms(50);
        __lcd_home();
        if (read_IR() == 1){              
            white_tape = 1;                //detect white_tape
            
            servoRotate_ConStop();
            break;
        }
    }
    servoRotate_ConStop();
    __delay_ms(100);
    counter = 0;   //initialize counter
    //compartment = init_position/5 -1;                                           //C0
    compartment = 0;        
    //start dispensing each compartment
    
    i = 0;
    while (i<7){         //only need to rotate 7 times
        if (compartment == 8){
            compartment = 0;
        }
        if (B_array[compartment] != 0){
            initLCD();
            printf("C%d",compartment);
            servoRotate_ConStop();           //start dispensing here
            __delay_ms(2000);
        }
        
        
        while(counter<=5){ 
                servoRotate_clockwise();         //rotate one compartment
                count_gear();
                initLCD();
                printf("%d",counter);
                __lcd_home();
                
            }

        counter = 0;
        compartment++;
        i++;
    }
    
    
    //close the lid and handle
    counter = 0;
    while(counter>=45){
        servoRotate_counter();
        count_gear();
    }
    
    /********test ADC value************/
       //printf("RA0: %.3x", readADC(0));
       //__lcd_newline();
       //printf("RA3: %.3x", readADC(3));
       //__delay_ms(400);
    /**********************************/   
        
    
}


void count_gear(){
    //count the gear teeth number, if prev = 0, count ++
    if (readADC(3)<250){       // original circuit = 150 
        if (prev == 0){
                initLCD();
                printf("%d",counter);
                __lcd_home();
                //__delay_ms();
                counter++;
                prev = 1;
        }
        else{
            prev = 0;
        }
                 
            
    }
}

int gear_bb_reading(){
    int reading_sum = 0;
    for (int i= 0; i < gear_breakbeam_size -1 ; i ++){
        reading_sum += gear_breakbeam[i+1];
        gear_breakbeam[i] = gear_breakbeam[i+1];
    }
    gear_breakbeam[gear_breakbeam_size - 1]=(int)(readADC(3));
    reading_sum += gear_breakbeam[gear_breakbeam_size - 1];
    return reading_sum / gear_breakbeam_size;
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

/****servo_Rotate code*/

void servoRotate_clockwise(){
      //PORTB as output
    for (i = 0; i<1; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(1400); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(18600);
    }
    //clockwise;
    
}

void servoRotate_ConStop(){   //stop
    for(i=0;i<50;i++)
    {
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(1500); // pulse of 1500us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(18500);
    }
}


void servoRotate_counter(){    //counterclockwise
      //PORTB as output
    for (i = 0; i<1; i++){
        LATDbits.LATD0 = 1;
        TRISDbits.RD0 = 0;
        __delay_us(2000); // pulse of 800us
        LATDbits.LATD0 = 0;
        TRISDbits.RD0 = 0;
        __delay_us(18000);
    }
    //clockwise;
    
}


int read_IR(){
    while(1){
        TRISCbits.RC0 = 1; //RA0
        unsigned char input = PORTCbits.RC0;
        //printf("input:");
        //putch(array[input]);
        //__delay_ms(500);
        //__lcd_home();
        if (array[input] == '1'){
            white_tape = 1;
            return 1;
        }
        else{
            return 0;
        }        
    }
}

void initialize_gear_breakbeam_history(){
    for (int i=0; i< gear_breakbeam_size; i++){
        gear_breakbeam[i] = 0;
    }
}