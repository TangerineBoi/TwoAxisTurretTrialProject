#include <Servo.h>
Servo baseServo;
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x68);
  baseServo.attach(2);
  //baseServo.write(90);
  Serial.begin(9600);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);  //turn on
  Wire.write(0x1B);
  Wire.write(0x06);
  Wire.endTransmission(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("from register: ");
  Wire.beginTransmission(0x68);
  Wire.write(0x3B); // X val
  Wire.requestFrom(0x3B, 14);
  Wire.endTransmission(true);
  
  /////

  Serial.println("request: ");
  Wire.beginTransmission(0x68);
  Wire.read();

  Wire.endTransmission(true);
  Serial.println(Wire.read());
  
  if(Wire.read() <= 180){
  baseServo.write(Wire.read());
  }
  delay(100);
}
