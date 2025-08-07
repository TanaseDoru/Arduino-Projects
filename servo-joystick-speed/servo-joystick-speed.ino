/**
***********
* SUMMARY *
***********

Sa se conecteze un servo pe pinul 8 si viteza acestuia va fi controlat de joystick (axa y)


**/
#include <Servo.h>
#define STOP

int yPin = A0;
int sleepTime = 1000;
const int DEFAULT_SLEEP = 15;
const int STATIONARY_VAL_JOYSTICK = 513;
const int DIVISION_FACTOR = 8;
Servo servo;

void setup() {
  Serial.begin(9600);

  servo.attach(8);
  servo.write(0);
}
void loop() {
#ifdef STOP
  return;
#endif
  int yVal;
  int angle;
   // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle+=2)  
  {                     
    yVal = analogRead(yPin);
    sleepTime = DEFAULT_SLEEP + (yVal - STATIONARY_VAL_JOYSTICK) / DIVISION_FACTOR;     
    if (sleepTime < 0 ) sleepTime = 1;           
    servo.write(angle);               
    delay(sleepTime);                   
    Serial.println(yVal);
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle-=2)    
  {                  
    yVal = analogRead(yPin);
    sleepTime = DEFAULT_SLEEP + (yVal - STATIONARY_VAL_JOYSTICK) / DIVISION_FACTOR;   
    if (sleepTime < 0 ) sleepTime = 1;           
    servo.write(angle);           
    delay(sleepTime);       
    Serial.println(yVal);
  } 
}