/*
  Keyestudio ESP32 Robot Arm
  9-3-5 tutorial code
  Function: joystick controls arm, axis z stores the rotation angle and re-plays the action
  http://www.keyestudio.com
*/
#include "ESP32Servo.h"
Servo base;  // create servo object to control a servo
Servo arm;
Servo forearm;
Servo gripper;
//Define servo control pin
#define basePin 16
#define armPin 17
#define forearmPin 2
#define gripperPin 4
//Define left joystick pin
#define left_B 12
#define left_X 13
#define left_Y 15
//Define right joystick pin
#define right_B 25
#define right_X 33
#define right_Y 32
int left_B_data, left_Y_data, left_X_data, right_B_data, right_X_data, right_Y_data;
//servo
int baseAngle = 90;     // initialize base servo angle
int armAngle = 90;      // initialize upper arm servo angle
int forearmAngle = 90;  // initialize forearm servo angle
int gripperAngle = 90;  // initialize claw servo angle

int attitude_data[4][11];
int base_attitude = 0;
int arm_attitude = 1;
int forearm_attitude = 2;
int gripper_attitude = 3;
int data_start_bit = 1;
int data_end_bit = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(left_B, INPUT);
  pinMode(left_X, INPUT);
  pinMode(left_Y, INPUT);
  pinMode(right_B, INPUT);
  pinMode(right_X, INPUT);
  pinMode(right_Y, INPUT);
  Serial.begin(9600);
  base.attach(basePin);  // attaches the servo on pin 16 to the servo object
  arm.attach(armPin);
  forearm.attach(forearmPin);
  gripper.attach(gripperPin);

  base.write(90);
  arm.write(90);
  forearm.write(90);
  gripper.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  left_B_data = digitalRead(left_B);
  left_X_data = analogRead(left_X);
  left_Y_data = analogRead(left_Y);

  right_B_data = digitalRead(right_B);
  right_X_data = analogRead(right_X);
  right_Y_data = analogRead(right_Y);

  attitude();
  baseControl();
  armControl();
  forearmControl();
  gripperControl();
}

//base control
void baseControl() {
  if (left_X_data > 3000) {
    while (analogRead(left_X) > 3000) {
      base.write(baseAngle++);
      if (baseAngle >= 180) baseAngle = 180;
      delay(10);
    }
  } else if (left_X_data < 20) {
    while (analogRead(left_X) < 20) {
      base.write(baseAngle--);
      if (baseAngle <= 0) baseAngle = 0;
      delay(10);
    }
  }
}

//upper arm control
void armControl() {
  if (left_Y_data > 3000) {
    while (analogRead(left_Y) > 3000) {
      arm.write(armAngle++);
      if (armAngle >= 180) armAngle = 180;
      delay(10);
    }
  } else if (left_Y_data < 20) {
    while (analogRead(left_Y) < 20) {
      arm.write(armAngle--);
      if (armAngle <= 80) armAngle = 80;
      delay(10);
    }
  }
}

//forearm control
void forearmControl() {
  if (right_Y_data < 30) {
    while (analogRead(right_Y) < 30) {
      forearm.write(forearmAngle++);
      if (forearmAngle >= 150) forearmAngle = 150;
      delay(10);
    }
  } else if (right_Y_data > 3000) {
    while (analogRead(right_Y) > 3000) {
      forearm.write(forearmAngle--);
      if (forearmAngle <= 30) forearmAngle = 30;
      delay(10);
    }
  }
}

//claw control
void gripperControl() {
  if (right_X_data > 3000) {
    while (analogRead(right_X) > 3000) {
      gripper.write(gripperAngle++);
      if (gripperAngle >= 150) gripperAngle = 150;
      delay(10);
      // gripper.write(180);
    }
  } else if (right_X_data < 20) {
    while (analogRead(right_X) < 20) {
      // gripper.write(80);
      gripper.write(gripperAngle--);
      if (gripperAngle <= 90) gripperAngle = 90;
      delay(10);
    }
  }
}

void attitude() {
  if (right_B_data == 1) {
    delay(10);  //eliminate button jitters
    if (right_B_data == 1) {

      attitude_data[base_attitude][data_start_bit] = base.read();
      delay(100);
      attitude_data[arm_attitude][data_start_bit] = arm.read();
      delay(100);
      attitude_data[forearm_attitude][data_start_bit] = forearm.read();
      delay(100);
      attitude_data[gripper_attitude][data_start_bit] = gripper.read();
      delay(100);
      data_start_bit++;
      data_end_bit = data_start_bit;
      if (data_start_bit > 10) data_start_bit = 10;
    }
  }
  if (left_B_data == 1) {
    delay(10);
    if (left_B_data == 1) {
      data_start_bit = 1;
      baseAngle = base.read();
      armAngle = arm.read();
      forearmAngle = forearm.read();
      gripperAngle = gripper.read();
      for (int i = 1; i < data_end_bit; i++) {
        //base
        if (baseAngle < attitude_data[base_attitude][i]) {
          while (baseAngle < attitude_data[base_attitude][i]) {
            base.write(baseAngle);
            delay(10);
            baseAngle++;
          }
        } else {
          while (baseAngle > attitude_data[base_attitude][i]) {
            base.write(baseAngle);
            delay(10);
            baseAngle--;
          }
        }
        //upper arm
        if (armAngle < attitude_data[arm_attitude][i]) {
          while (armAngle < attitude_data[arm_attitude][i]) {
            arm.write(armAngle);
            delay(10);
            armAngle++;
          }
        } else {
          while (armAngle > attitude_data[arm_attitude][i]) {
            arm.write(armAngle);
            delay(10);
            armAngle--;
          }
        }
        //forearm
        if (forearmAngle < attitude_data[forearm_attitude][i]) {
          while (forearmAngle < attitude_data[forearm_attitude][i]) {
            forearm.write(forearmAngle);
            delay(10);
            forearmAngle++;
          }
        } else {
          while (forearmAngle > attitude_data[forearm_attitude][i]) {
            forearm.write(forearmAngle);
            delay(10);
            forearmAngle--;
          }
        }
        //claw
        if (gripperAngle < attitude_data[gripper_attitude][i]) {
          while (gripperAngle < attitude_data[gripper_attitude][i]) {
            gripper.write(gripperAngle);
            delay(10);
            gripperAngle++;
          }
        } else {
          while (gripperAngle > attitude_data[gripper_attitude][i]) {
            gripper.write(gripperAngle);
            delay(10);
            gripperAngle--;
          }
        }
      }  //for end
    }
  }
}
