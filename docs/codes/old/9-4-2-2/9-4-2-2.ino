/*
  Keyestudio ESP32机械手臂
  9-4-2-2教程代码
  代码功能：连接WiFi并打印esp32的IP地址，并构建网页显示“Hello World！”
  http://www.keyestudio.com
*/
#include <WiFi.h>
#include <WebServer.h>

/*注意：
  ESP32只能连接频率为2.4GHz的wifi.
  如果你连接不上wifi可以检查wifi名称与密码与wifi频率.
  "your_SSID "替换成你是wifi名称
  "your_PASSWORD"替换成你的wifi连接密码*/
  
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WiFiServer server(80);  //设置网页端口为80，可以直接输入IP地址进入网页，不需要输入端口号

void setup() {
  Serial.begin(9600);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
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
}

void loop() {
  WiFiClient client = server.available();  //尝试接受一个从 WiFi 服务器传入的请求，并将其分配给一个名为 client 的 WiFiClient 对象。
  if (!client) {                           //这个条件判断语句检查是否成功接受了来自客户端的连接。如果没有成功接受连接，代码将立即退出函数。
    return;
  }
  Serial.println("New client");
  while (!client.available()) {           //这个循环将等待直到客户端发送了请求并且数据可用。在等待过程中，代码会以 1 毫秒的时间间隔进行延迟
    delay(1);
  }

  // HTML Page
 //字符串定义一个简单的 HTML 页面，其中包含一个标题 “Hello World!”。
 String webPage = "<html><head><title></title></head><body>";
  webPage += "<h1>Hello World!</h1>";
  webPage += "</body></html>";


  client.println("HTTP/1.1 200 OK");          //发送 HTTP 响应头，表示服务器成功处理了请求
  client.println("Content-Type: text/html");  //设置响应内容的类型为 HTML
  client.println("Connection: close");        //表示在完成响应后关闭与客户端的连接。
  client.println();                           //发送空行，表示 HTTP 响应头结束，正文内容即将开始。
  client.println(webPage);                    //发送之前定义的 HTML 页面内容给客户端，这样客户端将收到一个包含 “Hello World!” 的简单 HTML 页面作为响应。

  delay(100); // 添加延迟以确保响应完整发送
  client.stop(); // 关闭客户端连接
}
