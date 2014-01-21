/**
*******************************************************************************
ClassicDemo.ino

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

WiiClassic classic = WiiClassic();

void setup()
{
  delay(3000);
  Serial.begin(BAUDRATE);
  Serial.println("ready.");
  Wire.begin();
  classic.init();
}

void loop()
{

  //Face buttons.
  Serial.print(classic.upButton, DEC);
  Serial.print(' ');
  Serial.print(classic.downButton, DEC);
  Serial.print(' ');
  Serial.print(classic.leftButton, DEC);
  Serial.print(' ');
  Serial.print(classic.rightButton, DEC);
  Serial.print(' ');
  
  Serial.print(classic.aButton, DEC);
  Serial.print(' ');
  Serial.print(classic.bButton, DEC);
  Serial.print(' ');
  Serial.print(classic.xButton, DEC);
  Serial.print(' ');
  Serial.print(classic.yButton, DEC);
  Serial.print(' ');
  
  Serial.print(classic.selectButton, DEC);
  Serial.print(' ');
  Serial.print(classic.homeButton, DEC);
  Serial.print(' ');
  Serial.print(classic.startButton, DEC);
  Serial.print(' ');
  
  //Shoulder buttons.
  Serial.print(classic.lButton, DEC);
  Serial.print(' ');
  Serial.print(classic.rButton, DEC);
  Serial.print(' ');
  Serial.print(classic.zlButton, DEC);
  Serial.print(' ');
  Serial.print(classic.zrButton, DEC);
  Serial.print(' ');
  Serial.print(classic.lButtonAnalog, DEC);
  Serial.print(' ');
  Serial.print(classic.rButtonAnalog, DEC);
  Serial.print(' ');
  
  //Analog sticks.
  Serial.print(classic.leftAnalogY, DEC);
  Serial.print(' ');
  Serial.print(classic.leftAnalogX, DEC);
  Serial.print(' ');
  Serial.print(classic.rightAnalogY, DEC);
  Serial.print(' ');
  Serial.println(classic.rightAnalogX, DEC);
  
  classic.update();
  delay(10);
}
