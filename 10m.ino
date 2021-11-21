#include <Wire.h>
#define TEN_METER (15500)
long unsigned int encoder1Value = 0;
long unsigned int encoder2Value = 0;
long unsigned int encoder3Value = 0;
long unsigned int encoder4Value = 0;
long unsigned int target1 = 0;

void setup() {
  unsigned char i=0;
  pinMode(13,OUTPUT);//set output pin
  digitalWrite(13,LOW);
  Serial.begin(57600);//bit rate
  Wire.begin();
  delay(1000);//wait 1s
  target1 = 0x80000000 + TEN_METER;

  digitalWrite(13,HIGH);
  delay(1);
  Wire.beginTransmission(42);
  Wire.write("daffff");
  Wire.endTransmission();
  //Wire.write("daffff");
  Wire.beginTransmission(42);
  Wire.write("sa");//run forward
  
    Wire.write(99); Wire.write(0);//setting speed for 4 motors
    Wire.write(99); Wire.write(0);
    Wire.write(99); Wire.write(0);
    Wire.write(99); Wire.write(0);

  Wire.endTransmission();
}

void loop() {
  delay(1);
  Wire.write("daffff");//forward
  readEncoder();
  Serial.println("Encoder 1 read text!");  // Send some text to the PC
  Serial.println(encoder1Value);  // Send some text to the PC
  Serial.println("Encoder 2 read text!");  // Send some text to the PC
  Serial.println(encoder2Value);  // Send some text to the PC
  Serial.println("Encoder 3 read text!");  // Send some text to the PC
  Serial.println(encoder3Value);  // Send some text to the PC
  Serial.println("Encoder 4 read text!");  0-// Send some text to the PC
  Serial.println(encoder4Value);  // Send some text to the PC
  
  if (encoder1Value > 0x80040000)
  {encoder1Value=0x80000000;}
  else if (encoder1Value < 0x7FFC0000)
  {encoder1Value=0x80000000;}
  
  if (encoder1Value > target1)
  { Wire.beginTransmission(42);
    Wire.write("ha");//stop
    Wire.endTransmission();
    digitalWrite(13,HIGH);
    while(1);}
}

void readEncoder()
{
  long unsigned int encoder1 = 0;
  long unsigned int encoder2 = 0;
  long unsigned int encoder3 = 0;
  long unsigned int encoder4 = 0;
  Wire.beginTransmission(42);
  Wire.write("i");
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(42,8);
  delay(1);
  { encoder1 = (long unsigned int) Wire.read();
    encoder1 += ((long unsigned int) Wire.read() <<8);
    encoder1 += ((long unsigned int) Wire.read() <<16);
    encoder1 += ((long unsigned int) Wire.read() <<24);
    encoder2 = (long unsigned int) Wire.read();
    encoder2 += ((long unsigned int) Wire.read() <<8);
    encoder2 += ((long unsigned int) Wire.read() <<16);
    encoder2 += ((long unsigned int) Wire.read() <<24);}
    
  encoder1Value = encoder1;encoder2Value = encoder2;
  Wire.requestFrom(42,8);
  delay(1);
 
  { encoder3 = (long unsigned int) Wire.read();
    encoder3 += ((long unsigned int) Wire.read() <<8);
    encoder3 += ((long unsigned int) Wire.read() <<16);
    encoder3 += ((long unsigned int) Wire.read() <<24);
    encoder4 = (long unsigned int) Wire.read();
    encoder4 += ((long unsigned int) Wire.read() <<8);
    encoder4 += ((long unsigned int) Wire.read() <<16);
    encoder4 += ((long unsigned int) Wire.read() <<24);}
    
  encoder3Value = encoder3; encoder4Value = encoder4;  
}
