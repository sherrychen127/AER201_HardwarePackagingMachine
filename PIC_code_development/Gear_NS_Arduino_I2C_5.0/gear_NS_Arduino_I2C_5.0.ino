/* Arduino_I2C_PIC
 *  
 * Author: Sherry Chen
 * Date: March 27
 * 
 * Description: 
 *   gear detection using gear_Breakbeam
 *   integrate with IR reflective, stop when white tape detected. 
 *   integrate with Bolt/nuts/Spacer DC_motor and break_beam
 * Preconditions:
 *   1. PIC-Arduino link switches are enabled (ON) for A4 and A5 of the Arduino
 *      Nano (RC4 and RC3 for the primary PIC, respectively)
 *   2. PIC and Arduino Nano agree on the Arduino Nano's slave address (i.e. the
 *      same slave address is used in software)
 *   3. A PC is connected if the Arduino Nano serial monitor is to be used
 */

#include <Wire.h>
#include <Servo.h> 

Servo myservo_B;
Servo myservo_N;
Servo myservo_S;
Servo myservo_W;
Servo con_servo;

//DC motor pin assignment
int DC_motor0 = 2;    //PWM pins B   
int DC_motor1 = 5;     //N
int DC_motor2 = 6;     //S
int DC_motor3 = 3;     //W

int motor_speed = 170;

//IR sensor pin assignment
int IR_sensor = 4;  //pin D4
int IR_sensor_gear_analog = 0;   //the digital reading of IR sensor

//continuous servo pin assignment
int con_servo_pin = 9;
//gear breakbeam pin assignment
int gear_BR = A0;

//microservos pin assignments
int servo_motor0 = 7;   //bolt
int servo_motor1 = 11;   //nuts
int servo_motor2 = 12;   //spacer
int servo_motor3 = 8;    //washer



//gear counting variables
int gear_prev = 0;   //prev sensing gear_analogue for gear teeth
int gear_counter = 0;  //count number of gear teeth
int gear_analog; //gear_BR counter
int gear_rotate = 0;  // when = 1, start rotating (opening handles and detect white tape)
int openHandle_data_pic = 0; //determine when to send data to PIC to inform it that the C0 is found

//rotate one compartment
int rotate_oneCompartment = 0;   //uodate when receive '1' from pic
int rotate_oneCompartment_pic = 1;  //update when needs to send data to pic





//bolts variable
int B_ADC = A1; //Break beam sensor connect to A1
int B_analog = 0; //break beam sensor analog value
int B_dispense = 0; //variable that start dispense nuts when = 1;
int B_counter = 0;   //
int B_prev = 0; //previous break beam reading
int B_data_pic = 0; //send '2' to pic after dispensing one nut


//nuts variable
int N_ADC = A2; //Break beam sensor connect to A2
int N_analog = 0; //break beam sensor analog value
int N_dispense = 0; //variable that start dispense nuts when = 1;
int N_counter = 0;   //
int N_prev = 0; //previous break beam reading
int N_data_pic = 0; //send '3' to pic after dispensing one nut



//Spacer variable
int S_ADC = A3; //Break beam sensor connect to A3
int S_analog = 0; //break beam sensor analog value
int S_dispense = 0; //variable that start dispense nuts when = 1;
int S_counter = 0;   //
int S_prev = 0; //previous break beam reading
int S_data_pic = 0; //send '3' to pic after dispensing one nut



int close_lid = 0;  //if 1: start rotating counterclockwise for 50 gear teeth to close the lid
int close_lid_data_pic = 0;



void receiveEvent(void);
void requestEvent(void);

void rotate_compartment_function();


int nuts_dispense_function();  //return 1 when one nut dispensed
int bolts_dispense_function();
int spacers_dispense_function();


/*

unsigned char rotate_gear = '0';
unsigned char rotate_1compartment = '1';
unsigned char B_dispense = '2';
unsigned char N_dispense = '3';
unsigned char S_dispense = '4';

unsigned char motorStart_0 = '5';
unsigned char motorStop_0 = '6';

unsigned char motorStart_1 = '7';
unsigned char motorStop_1 = '8';

unsigned char motorStart_2 = '9';   //
unsigned char motorStop_2 = 10;

unsigned char motorStart_3 = 11;
unsigned char motorStop_3 = 12;

unsigned char servo_ramp = 13;
unsigned char close_handle = 14;
*/



//Sert UP ()
void setup(){
  myservo_B.attach(servo_motor0);
  myservo_N.attach(servo_motor1);
  myservo_S.attach(servo_motor2);
  myservo_W.attach(servo_motor3);
  
  con_servo.attach(con_servo_pin);
  

  // bolts natrual 90 ->0
  //washer natrual   150 -> 70
  //nuts natrual    60 -> 0
  //spacer       80-> 0
  
//initialize angle
  myservo_B.write(90); 
  myservo_N.write(60); 
  myservo_S.write(80); 
  myservo_W.write(130);   //caliberate

  pinMode(DC_motor0,OUTPUT);
  pinMode(DC_motor1,OUTPUT);
  pinMode(DC_motor2,OUTPUT);
  pinMode(DC_motor3,OUTPUT);

//break sensor pinmode
  pinMode(IR_sensor,INPUT);  //detect white tape_sensor A0

  


  pinMode(gear_BR,INPUT);  //gear break_beam sensor
  pinMode(N_ADC, INPUT); //nuts break beam sensor A2
  
  
  delay(1000);    
  Wire.begin(8); // Join I2C bus with address 8
  Wire.onReceive(receiveEvent); // Register a function to be called when this slave device receives a transmission from a master
  Wire.onRequest(requestEvent); // Register a function to be called when a master requests data from this slave device

  Serial.begin(9600); // Open serial port to PC (hardware UART)    
  
}



uint8_t state = 0;
uint8_t incomingByte;


void loop(){ 
  
  
  con_servo.writeMicroseconds(1500);
  //con_servo.detach();

  if (state && Serial.available() > 0 && !incomingByte) {
      incomingByte = Serial.read();
  }
  

  
 //Serial.println("gear_rotate");
 //Serial.print(gear_rotate);
  if (gear_rotate == 1){
    con_servo.attach(con_servo_pin);
    con_servo.write(83);
    while(1){
      
      gear_analog = analogRead(gear_BR);  //A0
      //Serial.println(gear_analog);
      if (gear_counter >= 55){
        break;
      }
      if (gear_analog<=260)
      {
        if (gear_prev == 0){
          
          gear_counter++;
          Serial.println(gear_counter);
        }

        gear_prev = 1;
        continue;
    
      }
      else if (gear_analog> 260){
        gear_prev = 0;
      }
    }
    con_servo.writeMicroseconds(1500);  //servo stop
    
    delay(800);
    Serial.println("start detecting white tape");

    con_servo.write(83);  //servo rotate
    while(1){
      IR_sensor_gear_analog = digitalRead(IR_sensor);
      //Serial.println(IR_sensor_gear_analog);
      if (IR_sensor_gear_analog == 0){    //0: detect  1:not detected
        con_servo.writeMicroseconds(1500);
        gear_counter = 0;
        //detected C0
        delay(800);
        openHandle_data_pic = 1;      //request event function send back '0' to indicate it is done
        break;
      }

    }
    con_servo.writeMicroseconds(1500);
    //con_servo.detach();
    delay(900);
    gear_rotate = 0;
  }


  
////rotate one compartment
  if (rotate_oneCompartment){ 
      //con_servo.attach(con_servo_pin);
      Serial.println("rotate_oneC");  
      con_servo.write(83);
      rotate_compartment_function();  //rotate one compartment
      con_servo.writeMicroseconds(1500); //stop servo
      delay(900);
      //con_servo.detach();  //detach servo
      rotate_oneCompartment = 0;  //reset
      rotate_oneCompartment_pic = 1;  //send data to pic
  }



//dispense bolts
  if (B_dispense){
   
    if (bolts_dispense_function()){
        B_data_pic = 1; //send char pic 
    }
    B_dispense = 0;
  }

  

//dispense nuts
//Serial.println(N_dispense);

  if (N_dispense){
    //Serial.println("N_dispense");
     if (nuts_dispense_function()){   //return 1 when one is dispensed
        N_data_pic = 1;  //send '3' to pic
     }
     N_dispense = 0;
     
  }

//dispense Spacer
  if (S_dispense){
    //analogWrite(DC_motor2,motor_speed);
    
    
    if (spacers_dispense_function()){
      S_data_pic = 1;
    }
    S_dispense = 0;
    
  }


//closing the lid, rotate counterclockwise to close the lid. 
  if (close_lid){
      Serial.println("closing the lid");
      con_servo.write(107);   //rotate counterclockwise
      while(1){
          gear_analog = analogRead(gear_BR);  //A0
          //Serial.println(gear_analog);
          if (gear_counter >= 50){
            break;
          }
          if (gear_analog<=260)
          { 
            if (gear_prev == 0){
                gear_counter++;
                Serial.println(gear_counter);
              }
            gear_prev = 1;
            continue;
    
          }
          else if (gear_analog> 260){
            gear_prev = 0;
          }
        }
      con_servo.writeMicroseconds(1500);  //servo stop
      close_lid = 0; //reset
      close_lid_data_pic = 0;   //send data to PIC
      delay(800);
  }


  

  

  
  
}


uint8_t buf[3];
uint8_t counter = 0;  



void receiveEvent(void){
  /* This function is called whenver a transmission is received from a master.
   * 
   * Arguments: none
   * 
   * Returns: none
   */
   
  uint8_t x = Wire.read(); // Receive byte
 
  gear_counter = 0;
  Serial.println(char(x));
  if (x == '0'){     //rotate 360+ degrees, and stop when detect the white tape
    Serial.println("start rotating");
    
     gear_rotate = 1;   //variable used for the conditional branch
      return;
    }
 

  if (x == '1'){    //rotate one compartment.
    gear_counter = 0;
    rotate_oneCompartment = 1;
    Serial.println("'1' received: rotate 1 Compartment");
  }
   
  if (x == '2'){    //dispense bolt
     B_dispense = 1;
     Serial.println("'2' received: dispense bolt");
  }
 
  if (x == '3'){    //dispense nuts
    N_dispense = 1;
    Serial.println("'3' received: dispense nuts");
  }


if (x == '4'){   //spacer dispense
    S_dispense = 1;
    
    Serial.println("'4' received: dispense spacer");
}

if (x == '5'){    // rotate bolts motor
    analogWrite(DC_motor0,motor_speed);
    Serial.println("'5' received: bolts motor rotate");
}

if (x == '6'){
  analogWrite(DC_motor0,0);    //stop bolts motor
  Serial.println("'6' received: bolts motor rotate");
}

if (x == '7'){
   analogWrite(DC_motor1,motor_speed);  //rotate nuts motor
   Serial.println("'7' received: nuts motor rotate");
}


if (x == '8'){
  analogWrite(DC_motor1,0);  //stop nuts motor
  Serial.println("'8' received: nuts motor stop");
}

if (x == '9'){
  Serial.println("data 9 received:Spacer motor rotate");
  analogWrite(DC_motor2,motor_speed);  //rotate spacer motor
}


if (x == 10){
  analogWrite(DC_motor2,0);    //stop spacer motor
  Serial.println("'10' received: Spacer motor rotate");
}

if (x == 11){
  analogWrite(DC_motor3,motor_speed);  //rotate washer motor
  Serial.println("'11' received: washer motor rotate");
}

if (x == 12){
  analogWrite(DC_motor3,0);   //stop washer motor
  Serial.println("'12' received:washer motor stop");
}

if (x == 13){    //rotate ramp_servo
    Serial.println("rotate Servo 2");
    myservo_B.write(0); 
    myservo_N.write(0); 
    myservo_S.write(0); 
    myservo_W.write(90); 
}

if (x == 14){   //close the lid
    close_lid = 1;   //update variable for main function
    Serial.println("close the lid");
}


if (x == 15){
    myservo_B.write(90); 
    myservo_N.write(60); 
    myservo_S.write(80); 
    myservo_W.write(130);
    Serial.println("initialize angle");
}
 


  
  //Serial.println((char)x); // Print to serial output as char (ASCII representation)

  //buf[counter++] = x;
  //counter = (counter == 3) ? 0 : counter;

  //if(buf[0]=='A' && buf[1]=='A' && buf[2]=='A'){
    //state = 1;
  //}
}






void requestEvent(void){
   /* This function is called whenver a master requests data.
   * 
   * Arguments: none
   * 
   * Returns: none
   */
   if (openHandle_data_pic){
      Serial.println("send '0' data to pic");
      Wire.write('0'); // Respond with message of 1 byte
      openHandle_data_pic = 0;
   }

   if (rotate_oneCompartment_pic){
      Serial.println("send data to pic: 1 compartment rotated");
      Wire.write('1');
      rotate_oneCompartment_pic = 0;  //reset
   }


   if (B_data_pic){
      Serial.println("send data to pic: 1 bolt dispensed");
      Wire.write('2');
      B_data_pic = 0; //reset
   }
   
   if (N_data_pic){
      Serial.println("send data to pic: 1 nut dispensed");
      Wire.write('3');
      //analogWrite(DC_motor1,0);
      N_data_pic = 0; //reset
   }
   if (S_data_pic){
      Serial.println("send Spacer dispensed");
      Wire.write('4');
      S_data_pic = 0;
   }

  if (close_lid_data_pic){
      Serial.println("closed the lid");
      Wire.write(14);
      close_lid_data_pic = 0;  //reset
  }
   
   else{
      Wire.write('a');
   }
  
}




//rotate one compartment
void rotate_compartment_function(){
  gear_counter = 0;
   while(1){
      
      gear_analog = analogRead(gear_BR);  //A0
      //Serial.println(gear_analog);
      if (gear_counter >= 5){
        break;
      }
      if (gear_analog<=260)
      {
        if (gear_prev == 0){
          gear_counter++;
          Serial.println(gear_counter);
        }

        gear_prev = 1;
        continue;  
      }
      else if (gear_analog> 260){
        gear_prev = 0;
      }
    }
    return;
}


int nuts_dispense_function(){
  N_counter = 0;
  while(1){
      //Serial.println("waiting");
      N_analog = analogRead(N_ADC);  //A2
      //Serial.println(N_analog);
      if (N_counter >=1 ){
        break;
      }
      if (N_analog<=260)
      {
        if (N_prev == 0){
          N_counter++;
          Serial.println("nuts counter:");
          Serial.println(N_counter);
        }

        N_prev = 1;
        continue;  
      }
      else if (N_analog> 260){
        N_prev = 0;
      }
    }
    return  1;
}


int bolts_dispense_function(){
  B_counter = 0;
  while(1){
      B_analog = analogRead(B_ADC);  //A2
      Serial.println(B_analog);
      if (B_counter >=1 ){
        break;
      }
      if (B_analog<=260)
      {
        if (B_prev == 0){
          B_counter++;
          Serial.println("bolts counter:");
          Serial.println(B_counter);
        }

        B_prev = 1;
        continue;  
      }
      else if (B_analog> 260){
        B_prev = 0;
      }
    }
    return  1;
}


int spacers_dispense_function(){
    Serial.println("entered function");
    S_counter = 0;
    while(1){
      S_analog = analogRead(S_ADC);  //A3
      Serial.println(S_analog);
    
      if (S_counter >=1 ){
        break;
      }
      if (S_analog<=260)
      {
        if (S_prev == 0){
          S_counter++;
          Serial.println("Spacers counter:");
          Serial.println(S_counter);
        }

        S_prev = 1;
        continue;  
      }
      else if (S_analog> 260){
        S_prev = 0;
      }
    }
    return  1;
}

