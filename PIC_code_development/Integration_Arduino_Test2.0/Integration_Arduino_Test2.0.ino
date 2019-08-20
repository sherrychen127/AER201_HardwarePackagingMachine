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

int compartment_array[8] = {0,0,0,0,0,0,0,0};   //which C is to be dispensed, index = compartment number {0,1,0,1,0,1,0,1};
int compartment_number[8] = {0,0,0,0,0,0,0,0}; //store the compartment number(index))

int B_array[8] = {0,0,0,0,0,0,0,0};                                               //change that!
int S_array[8] = {0,0,0,0,0,0,0,0}; 
int N_array[8]= {0,0,0,0,0,0,0,0};
int W_array[8]= {0,0,0,0,0,0,0,0};

Servo myservo_B;
Servo myservo_N;
Servo myservo_S;
Servo myservo_W;
Servo con_servo;

//DC motor pin assignment
int DC_motor0 = 3;    //PWM pins    
int DC_motor1 = 5;     //N
int DC_motor2 = 6;     //S
int DC_motor3 = 2;     //W

int motor_speed = 130;
int motor_speed 

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
int B_remain = 0;
int B_prev = 0; //previous break beam reading
int B_data_pic = 0; //send '2' to pic after dispensing one nut
int B_spacingTime = 0;

//nuts variable
int N_ADC = 10; //Break beam sensor connect to A2
int N_analog = 0; //break beam sensor analog value
int N_dispense = 0; //variable that start dispense nuts when = 1;
int N_counter = 0;   //
int N_remain = 0;
int N_prev = 0; //previous break beam reading
int N_data_pic = 0; //send '3' to pic after dispensing one nut
int N_spacingTime = 0;


//Spacer variable
int S_ADC = A2; //Break beam sensor connect to A2
int S_analog = 0; //break beam sensor analog value
int S_dispense = 0; //variable that start dispense nuts when = 1;
int S_counter = 0;   //
int S_remain = 0;
int S_prev = 0; //previous break beam reading
int S_data_pic = 0; //send '3' to pic after dispensing one nut
int S_spacingTime = 0;


//washer variable
int W_ADC = A3; //Break beam sensor connect to A3
int W_analog = 0; //break beam sensor analog value
int W_dispense = 0; //variable that start dispense nuts when = 1;
int W_counter = 0;   //
int W_remain = 0;
int W_prev = 0; //previous break beam reading
int W_data_pic = 0; //send '3' to pic after dispensing one nut
int W_spacingTime = 0;


int close_lid = 0;  //if 1: start rotating counterclockwise for 50 gear teeth to close the lid
int close_lid_data_pic = 0;



void receiveEvent(void);
void requestEvent(void);

void rotate_compartment_function();


int nuts_dispense_function();  //return 1 when one nut dispensed
int bolts_dispense_function();
int spacers_dispense_function();



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

  //pinMode(10,INPUT); //bolt analog pin  ///uncomment

//break sensor pinmode
  pinMode(IR_sensor,INPUT);  //detect white tape_sensor A0

  


  pinMode(gear_BR,INPUT);  //gear break_beam sensor
  pinMode(B_ADC, INPUT); //nuts break beam sensor A2
  pinMode(N_ADC, INPUT);
  pinMode(S_ADC, INPUT);
  pinMode(W_ADC, INPUT);
  
  delay(1000);    
  Wire.begin(8); // Join I2C bus with address 8
  Wire.onReceive(receiveEvent); // Register a function to be called when this slave device receives a transmission from a master
  Wire.onRequest(requestEvent); // Register a function to be called when a master requests data from this slave device

  Serial.begin(9600); // Open serial port to PC (hardware UART)    
  
}



uint8_t state = 0;
uint8_t incomingByte;


void loop(){ 
  /*
  analogWrite(DC_motor0,motor_speed);
  delay(100);
  analogWrite(DC_motor3,motor_speed);  //rotate washer
  N_counter = -1;
  
  while(1){
      B_analog = analogRead(A1);
      W_analog = analogRead(A3);
      //S_analog = analogRead(A2);
      //W_analog = analogRead(A3);
    if (B_spacingTime >= 10000){
       analogWrite(DC_motor0,0);
      //break;
    }
    //Serial.println(W_analog);
    if (B_analog<=250){
      if (B_prev == 0){
        B_spacingTime = 0;
          B_prev = 1;
          B_remain ++;
          Serial.print("B_remain:");
          Serial.println(B_remain);
          delay(100);
      }
      
    }
    
    if (B_analog>250){
        B_prev = 0;
    }


   
    
    if (W_spacingTime>=10000){
      analogWrite(DC_motor3,0);
      //break;
    }
    if (W_analog <= 250){
      if (W_prev == 0){
        W_spacingTime = 0;
          W_prev = 1;
          W_remain ++;
          Serial.print("W_remain:");
          Serial.println(W_remain);
          delay(100);
      }
      
    }

    if (W_analog >=250){
        W_prev = 0;
    }
    W_spacingTime += 20;
    B_spacingTime += 20;
    Serial.println(W_spacingTime);
    Serial.println(B_spacingTime);
  }


  delay(300);
  
  
  
  delay(20);
  
 
  
//spacer


  analogWrite(DC_motor2,motor_speed);
  delay(20);
  S_counter = 0;
  while(1){
    S_analog = analogRead(A2);
    if (S_counter >= 4){
      analogWrite(DC_motor2,0);
      break; 
    }
    if (S_analog <=350){
      if (S_prev == 0){
          S_prev = 1;
          S_counter ++;
          Serial.print("S_count:");
          Serial.println(S_counter);
          delay(200);
      }
    }
    else{
      S_prev = 0;
    
    }
 
  }
  


  
  //washer
  analogWrite(DC_motor3,motor_speed);
  delay(20);
  W_counter = 0;
  while(1){
    W_analog = analogRead(A3);
    if (W_counter >= 4){
      analogWrite(DC_motor3,0);
      break; 
    }
    if (W_analog <=350){
      if (W_prev == 0){
          W_prev = 1;
          W_counter ++;
          Serial.print("W_count:");
          Serial.println(W_counter);
          delay(200);
      }
    }
    else{
      W_prev = 0;
    
    }
 
  }
//dispense remaining fasteners
  analogWrite(DC_motor0,motor_speed);
  analogWrite(DC_motor1,motor_speed);
  analogWrite(DC_motor2,motor_speed);
  analogWrite(DC_motor3,motor_speed);

  
  while(1){
      B_analog = analogRead(A1);
      N_analog = digitalRead(10);
      S_analog = analogRead(A2);
      W_analog = analogRead(A3);
      
     if (B_spacingTime >= 4000){
       analogWrite(DC_motor0,0);
      break;
    }
    //Serial.println(W_analog);
    if (B_analog<=250){
      if (B_prev == 0){
          B_spacingTime = 0;
          B_prev = 1;
          B_remain ++;
          Serial.print("B_remain:");
          Serial.println(B_remain);
          delay(20);
      }
      
    }
    
    if (B_analog>250){
        B_prev = 0;
    }
    
//nuts
    if (N_spacingTime >= 4000){
       analogWrite(DC_motor1,0);
      break;
    }
    //Serial.println(W_analog);
    if (N_analog==0){
      if (N_prev == 0){
          N_spacingTime = 0;
          N_prev = 1;
          N_remain ++;
          Serial.print("N_remain:");
          Serial.println(N_remain);
          delay(20);
      }
      
    }
    
    if (N_analog>250){
        N_prev = 0;
    }
//spacer
if (S_spacingTime >= 4000){
       analogWrite(DC_motor2,0);
      break;
    }
    //Serial.println(W_analog);
    if (S_analog<=250){
      if (S_prev == 0){
          S_spacingTime = 0;
          S_prev = 1;
          S_remain ++;
          Serial.print("S_remain:");
          Serial.println(S_remain);
          delay(20);
      }
      
    }
    
    if (S_analog>250){
        S_prev = 0;
    }

    //washer
    if (W_spacingTime >= 4000){
       analogWrite(DC_motor3,0);
      break;
    }
    //Serial.println(W_analog);
    if (W_analog<=250){
      if (W_prev == 0){
          W_spacingTime = 0;
          W_prev = 1;
          W_remain ++;
          Serial.print("W_remain:");
          Serial.println(W_remain);
          delay(20);
      }
      
    }
    
    if (W_analog>250){
        W_prev = 0;
    }


    B_spacingTime+=40;
    N_spacingTime+=40;
    S_spacingTime+=40;
    W_spacingTime+=40;
    
  }
  
  

*/
}




void receiveEvent(void){
  /* This function is called whenver a transmission is received from a master.
   */
   printf("received");
   int i = 0;
   
   //if (Wire.read() == 100){
    while(Wire.available()){
      int c = Wire.read() - '0';
      compartment_array[i] = c;
      i ++;
   // }
      
    for (i = 0; i<8; i++){
      Serial.println(compartment_array[i]);
    }
   }
  
/*

  i = 0;
  if (Wire.read() == 101){
    while(Wire.available()){
      int b = Wire.read() - '0';
      int n = Wire.read() - '0';
      int s = Wire.read() - '0';
      int w = Wire.read() - '0';
      B_array[i] = b;
      N_array[i] = n;
      S_array[i] = s;
      W_array[i] = w;
      i ++;
    }
    Serial.println("B_array");
  for (i = 0; i<8; i++){
    Serial.println(B_array[i]);
  }

  Serial.println("N_array");
  for (i = 0; i<8; i++){
    Serial.println(N_array[i]);
  }


  Serial.println("S_array");
  for (i = 0; i<8; i++){
    Serial.println(S_array[i]);
  }


  Serial.println("W_array");
  for (i = 0; i<8; i++){
    Serial.println(W_array[i]);
  }
  
  }
  
*/
  
  return;


    
 
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

