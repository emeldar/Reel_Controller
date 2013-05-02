// --------------------------------------
// i2c_scanner V3
//Corrects two lines for device address mishandling.
//
// This program (or code that looks like it)
// can be found in many places.
// For example on the Arduino.cc forum.
// The original author is not know.
//
// This sketch tests the standard 7-bit addresses
// from 0 to 127. Devices with higher bit address
// might not be seen properly.
//
// Adapted to be as simple as possible by Arduino.cc user Krodal
//
// Feb 26 2013 - V3 by louarnold
// Using Arduino 1.0.1
//

#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Command Sender\n");
}


void loop()
{
  char inStr[16];
  int ind;
  int address = 0x12;
  int lsb;
  int msb;
  
  Serial.println("Waiting for primary command...");
  while(Serial.available() == 0){}
  
  ind = 0;
  while(Serial.available()){
    inStr[ind] = Serial.read();
    ind++;
    inStr[ind] = 0x00;
    delay(100);
  }
  lsb = atoi(inStr);
  
  Serial.print("Received a ");
  Serial.print(lsb,DEC);
  Serial.println(". Waiting for secondary command...");
  while(Serial.available() == 0){}
  
  ind = 0;
  while(Serial.available()){
    inStr[ind] = Serial.read();
    ind++;
    inStr[ind] = 0x00;
  }
  msb = atoi(inStr);
  
  Serial.print("Received a ");
  Serial.print(msb,DEC);
  Serial.println(". Now sending.\n");
  
    Wire.beginTransmission(address); //Correct.
    Wire.write(lsb);
    Wire.write(msb);
    Wire.endTransmission();
}
