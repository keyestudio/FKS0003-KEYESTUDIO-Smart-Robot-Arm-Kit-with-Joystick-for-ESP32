#include "ESP32Servo.h"

Servo myservo16;  // create servo object to control a servo
Servo myservo17;
Servo myservo18;
                // 16 servo objects can be created on the ESP32

int pos = 90;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin16 = 16;
int servoPin17 = 17;
int servoPin18 = 18;

void setup() {
  myservo16.attach(servoPin16);   // attaches the servo on pin 16 to the servo object
                              // using default min/max of 1000us and 2000us
                              // different servos may require different min/max settings
                              // for an accurate 0 to 180 sweep
  myservo17.attach(servoPin17);
  myservo18.attach(servoPin18);
  // myservo18.write(90);
  // myservo17.write(90);         // Set the servo angle to 90 degrees
  // delay(1000);
  // myservo17.write(0);         // Set the servo angle to 90 degrees
  // delay(1000);


}

void loop() {
  myservo16.write(0);
    myservo18.write(180);
    myservo17.write(90);
  // for (int i = 0; i < 180; i++) {
  //   myservo16.write(i);
  //   delay(5);
  // }
  //   for (int i = 180; i > 1; i--) {
  //   myservo16.write(i);
  //   delay(5);
  // }
}