/*
  Keyestudio ESP32 Robot Arm
  9-4-2 tutorial code
  Function: connect to wifi and print ESP32 IP address on the serial monitor
  http://www.keyestudio.com
*/
#include <WiFi.h>
// #include <WebServer.h>
/*ATTENTION:
  ESP32 only supports wifi at a frequency of 2.4GHz.
  If wifi fails to be connected, please check wifi name, passwords and frequency.
  Modify "your_SSID " into your wifi name
  Modify "your_PASSWORD" into your wifi passwords*/
  
 const char* ssid = "your_SSID";
 const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(9600);
  //initialize Wifi
  WiFi.begin(ssid, password);
  //search wifi. while loop: if no wifi is connected, keep searching; state: connecting
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  //wifi connected: print the IP address
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {
}