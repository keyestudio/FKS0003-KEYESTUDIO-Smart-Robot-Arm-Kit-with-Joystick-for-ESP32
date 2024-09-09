/*
  Keyestudio ESP32机械手臂
  9-1-7-1教程代码
  代码功能：控制舵机从0度缓慢的旋转到180度，然后再缓慢的从0度旋转到180度
  http://www.keyestudio.com
*/
#include <ESP32Servo.h>

// create a servo objects ，Customizable name
Servo servo;
int servoPin = 16; //定义IO16脚为舵机控制脚
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