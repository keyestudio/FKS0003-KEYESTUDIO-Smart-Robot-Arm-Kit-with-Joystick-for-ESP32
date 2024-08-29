/*
  Keyestudio ESP32 Robot Arm
  8-12 Servo Configuaration
  Function: set servo at pin IO16 to the angle of 90°
  http://www.keyestudio.com
*/
#include <ESP32Servo.h>

// create a servo objects ，Customizable name
Servo servo;
int servoPin = 16; //Connect servo to pin IO16

void setup()
{ 
  servo.attach(servoPin); 
  servo.write(0);  //set servo angle to 0°
  delay(1000);
  servo.write(180);  //set servo angle to 180°
  delay(1000);   
  servo.write(90);  //set servo angle to 90°
}

void loop() {
}
