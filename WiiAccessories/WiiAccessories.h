/**
*******************************************************************************
WiiAccessories.h

Underlying work: https://github.com/GabrielBianconi/ArduinoNunchuk
Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/

Derivative work: https://github.com/oldtopman/WiiAccessories
Copyright 2014 oldtopman, oldtopman <at> gmail <dot> com

Project URL: https://github.com/oldtopman/WiiAccessories

Project License: CC-BY-NC-SA - See SHARING for details.
*******************************************************************************
**/

#ifndef WII_ACCESSORIES_H
#define WII_ACCESSORIES_H

#include <Arduino.h>

class WiiNunchuk
{
  public:
    int analogX;
    int analogY;
    int accelX;
    int accelY;
    int accelZ;
    int zButton;
    int cButton;

    void init();
    void update();
};

class WiiMotionPlus
{
  public:
    int yaw;
    int pitch;
    int roll;
    
    void init();
    void update();
};

#endif
