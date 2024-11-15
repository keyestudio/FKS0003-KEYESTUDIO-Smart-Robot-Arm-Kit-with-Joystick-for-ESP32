/*
  Keyestudio ESP32 Robot Arm
  9-2 tutorial code
  Function: 
  http://www.keyestudio.com
*/
//Define the left remote rod pin
#define left_B 12  
#define left_X 13
#define left_Y 15
//Define the right remote rod pin
#define right_B 25
#define right_X 33
#define right_Y 32
//Define variables for storing remote sensing values
int left_B_data, left_Y_data, left_X_data, right_B_data, right_X_data, right_Y_data;  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(left_B, INPUT);   //Set pins to input mode
  pinMode(left_X, INPUT);
  pinMode(left_Y, INPUT);
  pinMode(right_B, INPUT);
  pinMode(right_X, INPUT);
  pinMode(right_Y, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  left_B_data = digitalRead(left_B);    
  left_X_data = analogRead(left_X);
  left_Y_data = analogRead(left_Y);

  right_B_data = digitalRead(right_B);
  right_X_data = analogRead(right_X);
  right_Y_data = analogRead(right_Y);

  Serial.print(" left B:");
  Serial.print(left_B_data);
  Serial.print("    left X:");
  Serial.print(left_X_data);
  Serial.print("    left Y:");
  Serial.println(left_Y_data);
  
  Serial.print("right B:");
  Serial.print(right_B_data);
  Serial.print("   right X:");
  Serial.print(right_X_data);
  Serial.print("   right Y:");
  Serial.println(right_Y_data);
  delay(300);
}
