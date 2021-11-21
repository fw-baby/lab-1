 #include <Wire.h>

long unsigned int encoder1Value = 0;
long unsigned int encoder2Value = 0;
long unsigned int encoder3Value = 0;
long unsigned int encoder4Value = 0;
//void readEncoder();
void setup() {
  unsigned char i=0;
  pinMode(13, OUTPUT);  // Configure the reset pin as an output and hold the robot in reset
  digitalWrite(13,LOW);
  Serial.begin(57600);
  Wire.begin(); // set Arduino nano board as master in I2C
  delay(1000);// wait 1 second
  digitalWrite(13,HIGH);  // Release the robot from reset
  delay(100);  // A short delay to allow the robot to start-up
}

void loop() {
        Wire.beginTransmission(42);//first line
        Wire.write("baffff");
        Wire.write(34);Wire.write(0);
        Wire.write(35); Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.endTransmission();
        delay(2200);
        
        Wire.beginTransmission(42);//first 90 degree
        Wire.write("barrff");//turn
        for(int i=1;i<=4;i++){
          Wire.write(41);Wire.write(0);
        }
        Wire.endTransmission();
        delay(948);

        Wire.beginTransmission(42);//second line
        Wire.write("baffff");
        Wire.write(34);Wire.write(0);
        Wire.write(35);Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.endTransmission();
        delay(2150);
        
        Wire.beginTransmission(42);//second 90 degree
        Wire.write("barrff");
        for(int i=1;i<=4;i++){
          Wire.write(41);Wire.write(0);
        }
        Wire.endTransmission();
        delay(968);

        Wire.beginTransmission(42);//third line
        Wire.write("baffff");
        Wire.write(34);Wire.write(0);
        Wire.write(35);Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.endTransmission();
        delay(2075);
        
        Wire.beginTransmission(42);//third 90 degree
        Wire.write("barrff");
        for(int i=1;i<=4;i++){
          Wire.write(41);Wire.write(0);
        }
        Wire.endTransmission();
        delay(960);
        
        Wire.beginTransmission(42);//fourth line
        Wire.write("baffff");
        Wire.write(34);Wire.write(0);
        Wire.write(35);Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.write(40);Wire.write(0);
        Wire.endTransmission();
        delay(2200);
        
        Wire.beginTransmission(42);//fourth 90 degree
        Wire.write("barrff");
        for(int i=1;i<=4;i++){
          Wire.write(41);Wire.write(0);
        }
        Wire.endTransmission();
        delay(1000);
  //delay(5);
  readEncoder();

  // set the reload value of encoder in both direction, take encoder_1 as reference
  if (encoder1Value > 0x80040000)
  {encoder1Value=0x80000000;}
  else if (encoder1Value < 0x7FFC0000)
  {encoder1Value=0x80000000;}
  Wire.beginTransmission(42);
  Wire.write("ha"); //Stop all the motors
  Wire.endTransmission();
  digitalWrite(13,HIGH);
  while(1); // end the movement
}

void readEncoder(){
  // four variables only valid inside the function
  long unsigned int encoder1 = 0;
  long unsigned int encoder2 = 0;
  long unsigned int encoder3 = 0;
  long unsigned int encoder4 = 0;
  
  Wire.beginTransmission(42);
  Wire.write("i");
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(42,8);
  delay(10);
  
  // length of long unsigned int is 4 bytes (32 bits), divide one package of data into 4 package (8 bits each)
  encoder1 = (long unsigned int) Wire.read(); // receive the encoder value from slave
  encoder1 += ((long unsigned int) Wire.read() <<8);
  encoder1 += ((long unsigned int) Wire.read() <<16);
  encoder1 += ((long unsigned int) Wire.read() <<24);
  encoder2 = (long unsigned int) Wire.read();
  encoder2 += ((long unsigned int) Wire.read() <<8);
  encoder2 += ((long unsigned int) Wire.read() <<16);
  encoder2 += ((long unsigned int) Wire.read() <<24);
  encoder1Value = encoder1;encoder2Value = encoder2;
  
  Wire.requestFrom(42,8);
  delay(10);
  encoder3 = (long unsigned int) Wire.read();
  encoder3 += ((long unsigned int) Wire.read() <<8);
  encoder3 += ((long unsigned int) Wire.read() <<16);
  encoder3 += ((long unsigned int) Wire.read() <<24);
  encoder4 = (long unsigned int) Wire.read();
  encoder4 += ((long unsigned int) Wire.read() <<8);
  encoder4 += ((long unsigned int) Wire.read() <<16);
  encoder4 += ((long unsigned int) Wire.read() <<24);
  encoder3Value = encoder3; encoder4Value = encoder4;  
}
