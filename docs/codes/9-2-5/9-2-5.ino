/*
  Keyestudio ESP32 Robot Arm
  9-2-5 tutorial code
  Function: read the value of the joystick in axis X Y Z
  http://www.keyestudio.com
*/
#define xPin 13  //define axis X pin to IO13
#define yPin 15   //define axis Y pin to IO15
#define buttonPin 12  //define axis z (button) to pin 12

int xData = 0;    //define a variable to store the analog value in axis x
int yData = 0;    //define a variable to store the analog value in axis y
int buttonData = 0;   //define a variable to store the digital value in axis z

void setup() {
  Serial.begin(9600);       //set the baud rate of the serial port
  pinMode(buttonPin, INPUT);  //set pin buttonPin to input.
}

void loop() {
  xData = analogRead(xPin); //read the analog value in axis x
  yData = analogRead(yPin); //read the analog value in axis y
  buttonData = digitalRead(buttonPin);  //read the button state and print it
  Serial.print("X:");     //monitor prints “X:”
  Serial.print(xData);    //print the analog value of  axis X
  Serial.print("     Y:");
  Serial.print(yData);
  Serial.print("     B:");
  Serial.println(buttonData);   //print the analog value of  axis Z(button) and wrap
  delay(100);   //delay 100ms

}