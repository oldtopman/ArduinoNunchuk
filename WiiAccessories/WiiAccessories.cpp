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

void BetaWiiClassic::init()
{
  sendByte(0x52, 0x40, 0x00);
  
  buttons[0] = 0xff;
  buttons[1] = 0xff;
  
  //First update initializes, slight delay for completion.
  BetaWiiClassic::update();
  delay(10);
  
  //Actual update call.
  BetaWiiClassic::update();
}

void BetaWiiClassic::update()
{
  int count = 0;
  
  //Send request for data.
  Wire.requestFrom(0x52, 6);
  
  //Signal data request to the classic controller.
  Wire.beginTransmission(0x52);
  Wire.write(0x00);
  Wire.endTransmission();
  
  //Get analog values.
  count = 0;
  while(count < 4)
  {
    values[count] = BetaWiiClassic::decoder(Wire.read());
    count++;
  }
  
  //Get buttons.
  count = 0;
  while(count < 2)
  {
    buttons[count] = BetaWiiClassic::decoder(Wire.read());
    count++;
  }
  
  /**
  ******************************
  ****Setting Button Values*****
  ******************************
  **/
  
  //Face Buttons.
  upButton = BetaWiiClassic::isPressed(1,0);
  downButton = BetaWiiClassic::isPressed(0,6);
  leftButton = BetaWiiClassic::isPressed(1,1);
  rightButton = BetaWiiClassic::isPressed(0,7);
  
  aButton = BetaWiiClassic::isPressed(1,4);
  bButton = BetaWiiClassic::isPressed(1,6);
  xButton = BetaWiiClassic::isPressed(1,3);
  yButton = BetaWiiClassic::isPressed(1,5);
  
  selectButton = BetaWiiClassic::isPressed(0,4);
  homeButton = BetaWiiClassic::isPressed(0,3);
  startButton = BetaWiiClassic::isPressed(0,2);
  
  //Shoulder buttons.
  lButton = BetaWiiClassic::isPressed(0,5);
  rButton = BetaWiiClassic::isPressed(0,1);
  zlButton = BetaWiiClassic::isPressed(1,7);
  zrButton = BetaWiiClassic::isPressed(1,2);
  lButtonAnalog = ((values[2] & 0x60) >> 2) + ((values[3] & 0xe0) >> 5);
  rButtonAnalog = values[3] & 0x1f;
  
  //Analog sticks.
  leftAnalogY = ( (values[1] & 0x3f) ); 
  leftAnalogX = ( (values[0] & 0x3f) );
  rightAnalogY = values[2] & 0x1f;  
  rightAnalogX = ((values[0] & 0xc0) >> 3) + ((values[1] & 0xc0) >> 5) +  ((values[2] & 0x80) >> 7);
}

//Checks certain bits for buttons.
boolean BetaWiiClassic::isPressed(byte p_row, byte p_bit)
{
  byte mask = (1 << p_bit);
  return ( !(buttons[p_row] & mask) );
}

//Decodes Classic controller bytes.
byte BetaWiiClassic::decoder(byte p_byte)
{
  return ((p_byte ^ 0x17) + 0x17);
}