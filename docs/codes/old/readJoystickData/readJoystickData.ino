/*
  Keyestudio ESP32机械手臂
  9-2-5教程代码
  代码功能，读取遥杆模块的值
  http://www.keyestudio.com
*/
#define xPin 13  //定义X轴的引脚为IO13
#define yPin 15   //定义Y轴的引脚为IO15
#define buttonPin 12  //定义z轴（按键）的引脚为12

int xData = 0;    //定义一个变量用来存放X轴读取出来的模拟值
int yData = 0;    //定义一个变量用来存放Y轴读取出来的模拟值
int buttonData = 0;   //定义一个变量用来存放Z轴（按键）读取出来的模拟值

void setup() {
  Serial.begin(9600);       //设置串口波特率
  pinMode(buttonPin, INPUT);  //设置buttonPin引脚为输入模式
}

void loop() {
  xData = analogRead(xPin); //读取遥感的X轴模拟值
  yData = analogRead(yPin); //读取遥感的Y轴模拟值
  buttonData = digitalRead(buttonPin);  //读取按钮的状态，并在下方打印出来
  Serial.print("X:");     //串口打印字符“X:”
  Serial.print(xData);    //串口打印X轴的模拟值
  Serial.print("     Y:");
  Serial.print(yData);
  Serial.print("     B:");
  Serial.println(buttonData);   //串口打印Z轴（按键）的值，并且换行
  delay(100);   //延时100ms

}