/**
*******************************************************************************
WiiAccessories-WMP.ino

Underlying work: https://github.com/GabrielBianconi/ArduinoNunchuk
Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/

Derivative work: https://github.com/oldtopman/WiiAccessories
Copyright 2014 oldtopman, oldtopman <at> gmail <dot> com

Project URL: https://github.com/oldtopman/WiiAccessories

Project License: CC-BY-NC-SA - See SHARING for details.
*******************************************************************************
**/

#include <Wire.h>
#include <WiiAccessories.h>

#define BAUDRATE 9600

WiiMotionPlus wmp = WiiMotionPlus();

void setup()
{
  delay(1000);
  Serial.begin(BAUDRATE);
  Wire.begin();
  wmp.init();
}

void loop()
{
  wmp.update();
  
  Serial.print(wiiMotionPlus.yaw, DEC);
  Serial.print(" ");
  Serial.print(wiiMotionPlus.pitch, DEC);
  Serial.print(" ");
  Serial.println(wiiMotionPlus.roll, DEC);
}