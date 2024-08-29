/*
  Keyestudio ESP32机械手臂
  9-4-2-1教程代码
  代码功能：连接wifi并在串口监视器中打印ESP32的IP地址
  http://www.keyestudio.com
*/
#include <WiFi.h>
// #include <WebServer.h>
/*注意：
  ESP32只能连接频率为2.4GHz的wifi.
  如果你连接不上wifi可以检查wifi名称与密码与wifi频率.
  "your_SSID "替换成你是wifi名称
  "your_PASSWORD"替换成你的wifi连接密码*/
  
 const char* ssid = "your_SSID";
 const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(9600);
  //初始化Wifi
  WiFi.begin(ssid, password);
  //寻找wifi，未连接成功，则一直处于连接中状态，while循环
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  //连接成功，打印 IP 地址
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {
}