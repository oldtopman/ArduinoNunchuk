/**
*******************************************************************************
WiiAccessories.cpp

Underlying work: https://github.com/GabrielBianconi/ArduinoNunchuk
Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/

Derivative work: https://github.com/oldtopman/WiiAccessories
Copyright 2014 oldtopman, oldtopman <at> gmail <dot> com

Project URL: https://github.com/oldtopman/WiiAccessories

Project License: CC-BY-NC-SA - See SHARING for details.
*******************************************************************************
**/
 * Based on the following resources:
 *   https://github.com/GabrielBianconi/ArduinoNunchuk
 *   http://www.windmeadow.com/node/42
 *   http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/
 *   http://wiibrew.org/wiki/Wiimote/Extension_Controllers

#include <Arduino.h>
#include <Wire.h>
#include "WiiAccessories.h"

static void sendByte(byte address, byte location, byte data)
{
  Wire.beginTransmission(address);

  Wire.write(location);
  Wire.write(data);

  Wire.endTransmission();

  delay(10);
}

void WiiNunchuk::init()
{
  sendByte(0x52, 0xF0, 0x55);
  sendByte(0x52, 0xFB, 0x00);

  WiiNunchuk::update();
}

void WiiNunchuk::update()
{
  int count = 0;
  int values[6];

  Wire.requestFrom(0x52, 6);

  while(Wire.available())
  {
    values[count] = Wire.read();
    count++;
  }

  WiiNunchuk::analogX = values[0];
  WiiNunchuk::analogY = values[1];
  WiiNunchuk::accelX = (values[2] << 2) | ((values[5] >> 2) & 3);
  WiiNunchuk::accelY = (values[3] << 2) | ((values[5] >> 4) & 3);
  WiiNunchuk::accelZ = (values[4] << 2) | ((values[5] >> 6) & 3);
  WiiNunchuk::zButton = !((values[5] >> 0) & 1);
  WiiNunchuk::cButton = !((values[5] >> 1) & 1);

  sendByte(0x52, 0x00, 0x00);
}

void WiiMotionPlus::init()
{
  //Initialize the WMP.
  //Note that it moves from 0x53 to 0x52.
  sendByte(0x53, 0xFE, 0x04);
  
  //Takes a while to start.
  delay(500);
  
  WiiMotionPlus::update();
}

void WiiMotionPlus::update()
{  
  int count = 0;
  int values[6];
  
  //Poke for data.
  //Not using sendByte as we don't do a full i2c...thing
  Wire.beginTransmission(0x52);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Wire.requestFrom(0x52, 6);
  
  while(Wire.available())
  {
    values[count] = Wire.read();
    count++;
  }
  
  WiiMotionPlus::yaw=((values[3]>>2)<<8)+values[0];
  WiiMotionPlus::pitch=((values[4]>>2)<<8)+values[1];
  WiiMotionPlus::roll=((values[5]>>2)<<8)+values[2];
}
  