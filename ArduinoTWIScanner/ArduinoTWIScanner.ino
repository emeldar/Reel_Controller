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
  Serial.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  //Note all I2C addresses are an even number.
  //The LSbit is used to indicate read or write.
  ///The Wire library wants a right-shifted address because
  //It left shifts them and puts in an LSbit of 1 for READ
  //or of 0 for WRITE and then sends the bit and address with it.
  //for(address = 0; address <= 127; address++ )//Incorrect
  for(address = 0; address <= 127; address++ )//Correct 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    //Wire.beginTransmission(address); //Incorrect.
    Wire.beginTransmission(address); //Correct.
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(3000);           // wait 8 seconds for next scan
}
