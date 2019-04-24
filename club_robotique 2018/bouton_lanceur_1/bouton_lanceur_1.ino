#include <Servo.h>
Servo myservo;


int pinStop = 15;
int pinStart = 13;
int etatStart = 1;
int etatStop = 0;
int stopM = 1;
int Thaut = 0;
int Tbas = 0;

void setup() {
  
 // myservo.attach(2);
 // myservo.writeMicroseconds(0);
//  myservo.write(0);
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW);
  Serial.begin(9600);
  pinMode(pinStop, INPUT);
  pinMode(pinStart, INPUT);
  
  while(etatStart == HIGH){
    Serial.println("wait");
    etatStart = digitalRead(pinStart);
    delay(30);
  }
  Serial.println("GO !");
}

void loop() {
  etatStop = digitalRead(pinStop);
  
  if (etatStop == HIGH){
    Serial.println("stop");
    stopM = 0;
    myservo.write(0);
  }
  if(stopM == 1){
    //myservo.writeMicroseconds(1600);
    //delay(30);
    //myservo.writeMicroseconds(1500);
  }
}
