/*
  Keyestudio ESP32 Robot Arm
  9-1-7-1 tutorial code
  Function: servo slowly rotates from 0° to 180°, and then slowly back to 0°
  http://www.keyestudio.com
*/
#include <ESP32Servo.h>

// create a servo objects ，Customizable name
Servo servo;
int servoPin = 16; //Connect the servo to pin IO16
int pos = 0;      // position in degrees

void setup()
{ 
  servo.attach(servoPin);   
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              
    delay(20);                       // waits 20ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // sweep from 180 degrees to 0 degrees
    servo.write(pos);
    delay(20);      
  }
}