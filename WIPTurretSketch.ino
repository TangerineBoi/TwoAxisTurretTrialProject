#include <Servo.h>
Servo baseServo;
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x68);
  baseServo.attach(2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Serial.println(Wire.endTransmission(false));

  Wire.requestFrom(0x68,1);
  Wire.onReceive(1);
  Serial.println(Wire.read());
  delay(500);
}
