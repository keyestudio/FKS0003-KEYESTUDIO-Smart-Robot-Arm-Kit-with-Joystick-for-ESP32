/*
  Keyestudio ESP32机械手臂
  8-12 组装设置舵机代码
  代码功能：将IO4引脚连接的舵机角度设置成90°
  http://www.keyestudio.com
*/
#include <ESP32Servo.h>

// create a servo objects ，Customizable name
Servo servo;
int servoPin = 16; //定义IO16脚为舵机控制脚

void setup()
{ 
  servo.attach(servoPin); 
  servo.write(0);  //设置舵机角度为90度
  delay(1000);
  servo.write(180);  //设置舵机角度为90度
  delay(1000);   
  servo.write(90);  //设置舵机角度为90度
}

void loop() {
}