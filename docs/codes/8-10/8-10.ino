/*
  Keyestudio ESP32 Robot Arm
  8-10 Servo Configuration
  Function: Set servo at pin IO4 to the angle of 90°
  http://www.keyestudio.com
*/
#include <ESP32Servo.h>

// create a servo objects ，Customizable name
Servo servo;
int servoPin = 4; //Connect servo to pin IO4

void setup()
{ 
  servo.attach(servoPin);
  servo.write(0);  //Set servo angle to 0°
  delay(1000);
  servo.write(180);  //Set servo angle to 180°
  delay(1000);   
  servo.write(90);  //Set servo angle to 90°
}

void loop() {
}