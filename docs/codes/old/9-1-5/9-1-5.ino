/*
  Keyestudio ESP32机械手臂
  9-1-5教程代码
  代码功能：控制舵机旋转到0度，90度，180度
  http://www.keyestudio.com
*/
#include <ESP32Servo.h>

// create a servo objects ，Customizable name
Servo servo;
int servoPin = 16; //定义IO16脚为舵机控制脚

void setup()
{ 
  servo.attach(servoPin);   
}

void loop() {
    servo.write(0);  //设置舵机角度为0度
    delay(1000);	//延时一秒
    servo.write(90);  //设置舵机角度为90度
    delay(1000);
    servo.write(180);  //设置舵机角度为180度
    delay(1000);
}