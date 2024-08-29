#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
/*注意：
  ESP32只能连接频率为2.4GHz的wifi.
  如果你连接不上wifi可以检查wifi名称与密码与wifi频率.
  "your_SSID "替换成你是wifi名称
  "your_PASSWORD"替换成你的wifi连接密码*/
// const char* ssid = "your_SSID";
// const char* password = "your_PASSWORD";
const char* ssid = "TEST1";
const char* password = "88888888";

WiFiServer server(80);  //设置网页端口为80，可以直接输入IP地址进入网页，不需要输入端口号

#define basePin 16    //定义底座舵机控制引脚为IO16
#define armPin 17     //定义大臂舵机控制引脚为IO17
#define forearmPin 2  //定义小臂舵机控制引脚为IO2
#define gripperPin 4  //定义夹子舵机控制引脚为IO4

Servo base;  // create servo object to control a servo
Servo arm;
Servo forearm;
Servo gripper;
int baseAngle, armAngle, forearmAngle, gripperAngle;  //用来存储舵机当前角度的变量

int slider1Value = 90;  // Default position
int slider2Value = 90;  // Default position
int slider3Value = 90;  // Default position
int slider4Value = 90;  // Default position

void setup() {
  Serial.begin(115200);
  base.attach(basePin);        // Connect base to pin 2
  arm.attach(armPin);          // Connect arm to pin 4
  forearm.attach(forearmPin);  // Connect forearm to pin 5
  gripper.attach(gripperPin);  // Connect gripper to pin 18
  delay(100);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //初始化Wifi
  WiFi.begin(ssid, password);
  //寻找wifi，未连接成功，则一直处于连接中状态，while循环
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  base.write(90);       //设置底座舵机的基础角度为90度
  delay(100);
  arm.write(90);        //设置大臂舵机的基础角度为90度
  delay(100);
  forearm.write(90);    //设置小臂舵机的基础角度为90度
  delay(100);
  gripper.write(90);    //设置爪子舵机的基础角度为90度
  delay(100);
}

void loop() {
  WiFiClient client = server.available();  //尝试接受一个从 WiFi 服务器传入的请求，并将其分配给一个名为 client 的 WiFiClient 对象。
  if (!client) {                           //这个条件判断语句检查是否成功接受了来自客户端的连接。如果没有成功接受连接，代码将立即退出函数。
    return;
  }
  // Serial.println("New client");
  while (!client.available()) {  //这个循环将等待直到客户端发送了请求并且数据可用。在等待过程中，代码会以 1 毫秒的时间间隔进行延迟
    delay(1);
  }

  String request = client.readStringUntil('\r');  // 读取客户端发送的HTTP请求，直到遇到回车符('\r')
  Serial.println(request);                        // 打印请求到串行监视器，方便调试
  client.flush();                                 // 清空客户端的输入缓冲区，确保没有残留数据

  baseAngle = base.read();        // 获取底座舵机当前角度
  armAngle = arm.read();          // 获取大臂舵机当前角度
  forearmAngle = forearm.read();  // 获取小臂舵机当前角度
  gripperAngle = gripper.read();  // 获取夹子舵机当前角度

  // 在请求字符串中查找"slider1="、"slider2="、"slider3="和"slider4="的位置
  int pos1 = request.indexOf("slider1=");
  int pos2 = request.indexOf("slider2=");
  int pos3 = request.indexOf("slider3=");
  int pos4 = request.indexOf("slider4=");

  // 如果找到了"slider1="，则提取其后的值并转换为整数，然后调用baseControl函数控制底座舵机
  if (pos1 != -1) {
    int val1 = request.substring(pos1 + 8, pos1 + 11).toInt();  //找到数据并提取出来
    baseControl(val1);                                          //将值给baseControl控制左击
  }
  // 类似地，对于其他三个slider，也执行相同的操作
  if (pos2 != -1) {
    int val2 = request.substring(pos2 + 8, pos2 + 11).toInt();
    armControl(val2);
  }
  if (pos3 != -1) {
    int val3 = request.substring(pos3 + 8, pos3 + 11).toInt();
    forearmControl(val3);
  }
  if (pos4 != -1) {
    int val4 = request.substring(pos4 + 8, pos4 + 11).toInt();
    gripperControl(val4);
  }

  // HTML Page
  String webPage = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>ESP32 Servo Control</title>\
<style>body {font-family: Arial, sans-serif;background-color: #f5f5f5;margin: 0;padding: 0;}\
.container {max-width: 100%;margin: 20px auto;padding: 20px;background-color: #fff;border-radius: 10px;box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);}\
h1 {text-align: center;color: #333;}\
.gauge-container {display: flex;align-items: center;margin-bottom: 20px;width: 100%;}\
.gauge-label {flex: 1;text-align: right;margin-right: 10px;font-weight: bold;color: #333;}\
.gauge {flex: 2;position: relative;width: 100px;height: 50px;}\
.gauge:before {content: '';position: absolute;width: 100%;height: 50%;background: #ddd;border-top-left-radius: 100px;border-top-right-radius: 100px;top: 0;left: 0;}\
.gauge:after {content: '';position: absolute;width: 100%;height: 50%;background: #fff;border-top-left-radius: 100px;border-top-right-radius: 100px;top: 2px;left: 0;z-index: 1;}\
.gauge .needle {width: 3px;height: 50px;background: #007bff;position: absolute;top: 0;left: 50%;transform-origin: 50% 100%;z-index: 2;}\
.gauge .value {position: absolute;width: 100%;text-align: center;top: 50px;left: 0;font-weight: bold;color: #333;}\
input[type=\"range\"] {width: calc(100% - 20px);-webkit-appearance: none;appearance: none;height: 10px;border-radius: 5px;background-color: #ddd;outline: none;margin-top: 10px;margin-bottom: 20px;}\
input[type=\"range\"]::-webkit-slider-thumb {-webkit-appearance: none;appearance: none;width: 20px;height: 20px;border-radius: 50%;background-color: #007bff;cursor: pointer;}\
</style></head><body>\
<div class=\"container\"><h1>ESP32 Servo Control</h1>\
<div class=\"gauge-container\"><div class=\"gauge-label\">Base Servo</div><div class=\"gauge\"><div id=\"needle1\" class=\"needle\" style=\"transform: rotate(0deg);\"></div><div id=\"value1\" class=\"value\">90</div></div></div>\
<input type=\"range\" min=\"0\" max=\"180\" value=\"90\" onchange=\"update(this.value, '1')\">\
<div class=\"gauge-container\"><div class=\"gauge-label\">Arm Servo</div><div class=\"gauge\"><div id=\"needle2\" class=\"needle\" style=\"transform: rotate(0deg);\"></div><div id=\"value2\" class=\"value\">90</div></div></div>\
<input type=\"range\" min=\"0\" max=\"180\" value=\"90\" onchange=\"update(this.value, '2')\">\
<div class=\"gauge-container\"><div class=\"gauge-label\">Forearm Servo</div><div class=\"gauge\"><div id=\"needle3\" class=\"needle\" style=\"transform: rotate(0deg);\"></div><div id=\"value3\" class=\"value\">90</div></div></div>\
<input type=\"range\" min=\"0\" max=\"180\" value=\"90\" onchange=\"update(this.value, '3')\">\
<div class=\"gauge-container\"><div class=\"gauge-label\">Gripper Servo</div><div class=\"gauge\"><div id=\"needle4\" class=\"needle\" style=\"transform: rotate(0deg);\"></div><div id=\"value4\" class=\"value\">90</div></div></div>\
<input type=\"range\" min=\"0\" max=\"180\" value=\"90\" onchange=\"update(this.value, '4')\"></div>\
<script>function update(val, slider) {\
var xhttp = new XMLHttpRequest();\
xhttp.open('GET', '?' + 'slider' + slider + '=' + val, true);\
xhttp.send();\
document.getElementById('value' + slider).innerHTML = val;\
var rotation = (val - 90) * (180 / 180);\
document.getElementById('needle' + slider).style.transform = 'rotate(' + rotation + 'deg)';\
}</script></body></html>";

  client.println("HTTP/1.1 200 OK");          //发送 HTTP 响应头，表示服务器成功处理了请求
  client.println("Content-Type: text/html");  //设置响应内容的类型为 HTML
  client.println("Connection: close");        //表示在完成响应后关闭与客户端的连接。
  client.println();                           //发送空行，表示 HTTP 响应头结束，正文内容即将开始。
  client.println(webPage);                    //发送之前定义的 HTML 页面内容给客户端，这样客户端将收到一个包含 “Hello World!” 的简单 HTML 页面作为响应。
}

//底座控制
void baseControl(int angle) {
  int angleVal = map(angle, 0, 180, 180, 0);  //使用map函数将0-180的值映射成180-0的值
  Serial.println(angleVal);
  if (angleVal > baseAngle) {                 //当前网页滑块的值是否大于舵机角度（滑块的值是0-180）
    while (angleVal > baseAngle) {            //如果滑块的值大于舵机角度，则使用while以10ms加一度的速度进行允许知道舵机角度等于滑块值
      base.write(baseAngle++);                //设置多久角度,"baseAngle++"baseAngle加一代码
      if (baseAngle >= 180) baseAngle = 180;  //设置baseAngle值的上限
      delay(10);                              //延时10ms
    }
  } else if (angleVal < baseAngle) {      //判断滑块的值是否小于舵机当前角度
    while (angleVal < baseAngle) {        //如果滑块的值小于舵机角度，则使用while以10ms减一度的速度进行允许知道舵机角度等于滑块值
      base.write(baseAngle--);            //设置多久角度,"baseAngle--"baseAngle减一一代码
      if (baseAngle <= 0) baseAngle = 0;  //设置baseAngle值的下限
      delay(10);
    }
  }
}
//下面三个函数与baseControl函数的逻辑一样，不一样的是角度映射不一样，因为结构等原因，有些舵机的旋转范围不能达到0-180，所以将范围进行调整
//大臂控制
void armControl(int angle) {
  int angleVal = map(angle, 0, 180, 80, 180);
  if (angleVal > armAngle) {
    while (angleVal > armAngle) {
      arm.write(armAngle++);
      if (armAngle >= 180) armAngle = 180;
      delay(10);
    }
  } else if (angleVal < armAngle) {
    while (angleVal < armAngle) {
      arm.write(armAngle--);
      if (armAngle <= 80) armAngle = 80;
      delay(10);
    }
  }
}

//小臂控制
void forearmControl(int angle) {
  int angleVal = map(angle, 0, 180, 30, 150);
  if (angleVal > forearmAngle) {
    while (angleVal > forearmAngle) {
      forearm.write(forearmAngle++);
      if (forearmAngle >= 150) forearmAngle = 150;
      delay(10);
    }
  } else if (angleVal < forearmAngle) {
    while (angleVal < forearmAngle) {
      forearm.write(forearmAngle--);
      if (forearmAngle <= 30) forearmAngle = 30;
      delay(10);
    }
  }
}

//爪子控制
void gripperControl(int angle) {
  int angleVal = map(angle, 0, 180, 85, 150);
  if (angleVal > gripperAngle) {
    while (angleVal > gripperAngle) {
      gripper.write(gripperAngle++);
      if (gripperAngle >= 150) gripperAngle = 150;
      delay(10);
    }
  } else if (angleVal < gripperAngle) {
    while (angleVal < gripperAngle) {
      gripper.write(gripperAngle--);
      if (gripperAngle <= 85) gripperAngle = 85;
      delay(10);
    }
  }
}
