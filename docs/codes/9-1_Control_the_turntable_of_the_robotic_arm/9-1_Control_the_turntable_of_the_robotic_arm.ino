/*
  Keyestudio ESP32 Robot Arm
  9-1 tutorial code
  Function: control the servo to rotate to 0°, 90°, 180°
  http://www.keyestudio.com
*/
#include <ESP32Servo.h>

// create a servo objects ，Customizable name
Servo servo;
int servoPin = 16; //Connect servo to pin IO16

void setup()
{ 
  servo.attach(servoPin);   
}

void loop() {
    servo.write(0);  //Set servo angle to 0°
    delay(1000);	//Delay 1s
    servo.write(90);  //Set servo angle to 90°
    delay(1000);
    servo.write(180);  //Set servo angle to 180°
    delay(1000);
}