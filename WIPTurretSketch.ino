#include <Servo.h>
Servo baseServo;
#include <Wire.h>

int servoX = 0;

int counter = 0;
void setup() {
  // put your setup code here, to run once:
  Wire.setClock(400000);
  Wire.begin(0x68);
  baseServo.attach(2);
  baseServo.write(90);

  Serial.begin(9600);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); //turn on
  Wire.write(0);  //turn on
  //Wire.write(0x1B);
  //Wire.write(0x06);
  Wire.endTransmission(true);
  Wire.beginTransmission(0x68);
  Wire.write(0x1B); //turn on
  Wire.write(0x8);
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("from register: ");
///Serial.println(wireReadX);


//X axis
  // Wire.beginTransmission(0x68);
  // Serial.println("X transmission: ");
  // Wire.write(0x43);

  // Wire.endTransmission(false);
  // /////
  // Wire.requestFrom(0x68, 7);
  

  // X axis 

  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);

  Wire.requestFrom(0x68, 2);

  int16_t wireReadX = Wire.read() << 8  | Wire.read();
  int16_t wireReadY = Wire.read() << 8  | Wire.read();
  wireReadX /= -12;
  Serial.println(wireReadX);
  

  counter++;
  if (counter == 10){
    Serial.println(wireReadX);
    Wire.read();
    if(wireReadX >= 255){
      baseServo.write(255);
    }
    else if(wireReadX <= -255){
      baseServo.write(-255);  
    }
    else{
          baseServo.write(wireReadX/2);
    }
    //servoX += wireReadX;     ///dunno
    counter = 0;
  }
  
  
  delay(200);
}
