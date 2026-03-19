#include <Servo.h>
Servo baseServo;
Servo turretServo;
#include <Wire.h>
int Zvalsteady = 0;
int counter = 0;
int totalX = 0;
int totalY = 0;
int totalZ = 0;

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
  Wire.write(0x6B);  //absolutely crucial
  Wire.write(0);   
  Wire.endTransmission(true);
  Wire.beginTransmission(0x68);
  //Wire.write(0x1B);  //gyro setup
  //Wire.write(2);
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
  Wire.write(0x47);  //3F or 47
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2);
  int16_t wireReadZ = Wire.read() << 8 | Wire.read();

  int Xval = wireReadX / 1000;  //x val
  int Yval = wireReadY / 1000;  //y val
  int Zval = wireReadZ / 1000;  //z val    

  Xval = (90 + (Xval * 5));
  Yval = (90 + (Yval * 5));
  Zval = (90 + (Zval * 5));


  //X AXIS
  Serial.print("X value: ");   //print X
  Serial.print(Xval);       //print X
  baseServo.write(Xval);
  //Y AXIS
  Serial.print(" Y value: ");  //print Y
  Serial.print(Yval);       //print Y
  turretServo.write(Yval);
  //Z axis
  Serial.print(" Z value: ");   //print Z
  if (Zval > Zvalsteady) {
    Zvalsteady = Zval;
  } else if (Zval < Zvalsteady) {
    Zvalsteady = Zval;
  }

  Serial.println(Zvalsteady - 85);   //print Z
  
  
  if(counter == 100){
    Serial.print("** X Mean: ");
    Serial.print(totalX / 100);
    Serial.print(" Y Mean: ");
    Serial.print(totalY / 100);
    Serial.print(" Z Mean: ");
    Serial.println(totalZ / 100);
    counter = 0;
    totalX = 0;
    totalY = 0;
    totalZ = 0;
  }
  counter++;
  totalX += Xval;
  totalY += Yval;
  totalZ += Zval;
  
  delay(100);
}
