#include <Servo.h>
Servo baseServo;
Servo turretServo;
#include <Wire.h>

int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.setClock(400000);
  Wire.begin(0x68);
  baseServo.attach(2);
  baseServo.write(90);
  turretServo.attach(4);
  turretServo.write(90);

  Serial.begin(9600);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);  //turn on
  Wire.write(0);     //turn on
  Wire.endTransmission(true);
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);  //turn on
  Wire.write(0x8);
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  // X axis
  Wire.beginTransmission(0x68);
  Wire.write(0x3D);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2);
  int16_t wireReadX = Wire.read() << 8 | Wire.read();

  // Y axis
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2);
  int16_t wireReadY = Wire.read() << 8 | Wire.read();

  // Z axis
  Wire.beginTransmission(0x68);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2);
  int16_t wireReadZ = Wire.read() << 8 | Wire.read();

  counter++;

  int Xval = wireReadX / 1000;  //x val
  int Yval = wireReadY / 1000;  //y val
  int Zval = wireReadZ; //z val    ///////TEMP CHANGE
  Xval = (90 + (Xval * 5));
  Yval = (90 + (Yval * 5));
  Zval = (90 + (Zval * 5));

  if (counter == 1) {
    //X AXIS
    Serial.print("X value: ");
    Serial.print(Xval);
    baseServo.write(Xval);
    //Y AXIS
    Serial.print(" Y value: ");
    Serial.print(Yval);
    turretServo.write(Yval);
    //Z axis
    Serial.print(" Z value: ");
    Serial.println(Zval);
    counter = 0;
  }


  delay(100);
}
