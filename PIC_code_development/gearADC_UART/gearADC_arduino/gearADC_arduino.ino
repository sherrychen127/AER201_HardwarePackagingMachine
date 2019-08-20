#include<Servo.h>
Servo myservo;

int val;
int num = 0;
int prev = 0;
void setup() {
  Serial.begin(9600);
  myservo.attach(9);

}

void loop() {
  myservo.write(83);
  val = analogRead(A0);
  
  //Serial.println(val);
  
  if (val<=200)
  {
    
    if (prev == 0){
      num++;
      Serial.println(num);
    }
    else{
      num = num;
    }
    prev = 1;
    
  }
  else{
    prev = 0;
  }
  delay(10);
}
