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
  Serial.println("\nI2C Command Sender");
}


void loop()
{
  byte commands[6] = {1, 2, 3, 4, 5, 6};
  byte address = 0x12;
  byte com;

  for(com = 0; com <= 5; com++ )
  {
    
    Wire.beginTransmission(address); //Correct.
    Wire.write(8);
    Wire.write(commands[com]);
    Wire.endTransmission();
    Serial.print("Sent a 8 then a ");
    Serial.println(commands[com],DEC);
    delay(1000);           // wait 8 seconds for next scan
  }
}
