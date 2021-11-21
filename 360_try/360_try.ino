#include <Wire.h>
#define SPIN (650)
long unsigned int encoderValue = 0;
long unsigned int target = 0;

void setup() {
pinMode(13, OUTPUT);
digitalWrite(13,LOW);
Wire.begin();
target = 0x80000000 + SPIN;
delay(3000); //wait 3 seconds
digitalWrite(13,HIGH);
delay(100); // A short delay to allow the robot to start-up
Wire.beginTransmission(42);
Wire.write("d1r"); delay(20); //set direction
Wire.write("d3r"); delay(20);
Wire.write("sa"); delay(20); //set speed
for(int i=0;i<=3;i++)
{
Wire.write(46);
Wire.write(0);
}
Wire.endTransmission();
}

 void loop() {
 delay(10);
 readEncoder();
 if (encoderValue > target)
 {
 Wire.beginTransmission(42); //Stop all the motors
 Wire.write("ha");
 Wire.endTransmission();
 digitalWrite(13,HIGH);
 while(1);
 }
 }

 void readEncoder()
 {
 long unsigned int encoder1 = 0;
 Wire.beginTransmission(42);
 Wire.write("i");
 Wire.endTransmission();

 delay(1);
 Wire.requestFrom(42,8);
 delay(10);
 encoder1 = (long int) Wire.read();
 encoder1 += ((long int) Wire.read() <<8);
 encoder1 += ((long int) Wire.read() <<16);
 encoder1 += ((long int) Wire.read() <<24);
 encoderValue = encoder1;
 }
