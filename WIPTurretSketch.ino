#include <Servo.h>
Servo baseServo;
#include <Wire.h>
int wireReadPrevious = Wire.read();
int counter = 0;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x68);
  baseServo.attach(2);
  //baseServo.write(90);
  Serial.begin(9600);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); //turn on
  Wire.write(0);  //turn on
  //Wire.write(0x1B);
  //Wire.write(0x06);
  Wire.endTransmission(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("from register: ");

  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  /////
  Wire.requestFrom(0x68, 4);
  Serial.print("read: ");

  counter++;

  if (Wire.available() && counter == 2){
    Serial.println(Wire.read());
    wireReadPrevious = Wire.read();
    baseServo.write(Wire.read());
    counter = 0;
    delay(10);
  }
  
  
  delay(200);
}
