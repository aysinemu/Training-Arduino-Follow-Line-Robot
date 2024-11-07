#include <AFMotor.h>
#include <Servo.h>
#include "SoftwareSerial.h"
Servo servo1;
SoftwareSerial HC05 (0, 1); //TX, RX
#define LeftMid A3
#define LeftOut A2
#define RightMid A4
#define RightOut A5
const int trigPin = 2;
const int echoPin = 13;
char dieu_khien;
AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(4, MOTOR12_64KHZ);
long duration;
int distance;
int vitri = 0;
int LM = 0;
int LO = 0;
int RM = 0;
int RO = 0;
int NumL = 0;
int NumR = 0;
int mode = 0;

void setup() {
  Serial.begin(9600);
  HC05.begin(9600);
  servo1.attach(10);
  servo1.write(vitri);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  motor1.setSpeed(225);
  motor2.setSpeed(225);
  motor3.setSpeed(225);
  motor4.setSpeed(225);
}

void loop() {
//   sound();
//  Serial.print(mode);
  if(analogRead(LeftMid) < 50){
    LM = 1;
  }else if(analogRead(LeftMid) > 1000){
    LM = 0;
  }
//  Serial.print(LM);
  if(analogRead(RightMid) < 50){
    RM = 1;
  }else if(analogRead(RightMid) > 1000){
    RM = 0;
  }
//  Serial.print(RM);
  if(analogRead(LeftOut) < 50){
    LO = 1;
  }else if(analogRead(LeftOut) > 1000){
    LO = 0;
  }
//  Serial.print(LO);
  if(analogRead(RightOut) < 50){
    RO = 1;
  }else if(analogRead(RightOut) > 1000){
    RO = 0;
  }
//  Serial.print(RO);
//  line();
   if (HC05.available() > 0) 
  {
    dieu_khien = HC05.read();
    Serial.println(dieu_khien);
    switch (dieu_khien) 
    {
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'S':
        breaker();
        break;
    }
  }
}

void forward(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void backward(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void breaker(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void right(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void left(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void line(){
  NumL = LM + LO;
  NumR = RM + RO;
  if (NumL == 2 and NumR == 2){
    forward();
  }else if (NumL > NumR){
    right();
  }else if (NumR < NumL){
    left();
  }else{
    breaker();
  }
}

void sound(){
  for(int i = 0;i <= 180;i++){
    servo1.write(i);
    distancee();
    delay(50);
  }
}

void distancee(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);
}
