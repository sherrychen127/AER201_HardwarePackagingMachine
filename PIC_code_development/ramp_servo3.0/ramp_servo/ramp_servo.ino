#include <Wire.h>
#include <Servo.h> 

Servo myservo_B;
Servo myservo_N;
Servo myservo_S;
Servo myservo_W;
Servo myservo_test;

void setup(){
  myservo_N.attach(5);
  //myservo_N.attach(A1);
  //myservo_S.attach(A2);
  //myservo_W.attach(A3); 

  //myservo_test.attach(A4);

  // bolts natrual 90 ->0
//washer natrual 150 -> 70
//nuts natrual 60 -> 0
//spacer 80-> 0
  
 

  Serial.begin(9600);

}
void loop(){

    myservo_N.write(0);  
    delay(3000);
    //myservo_N.write(60);
    delay(3000);
}

