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
    bool zButton;
    bool cButton;

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

class WiiClassic
{
  public:
    
    //Face buttons.
    bool upButton;
    bool downButton;
    bool leftButton;
    bool rightButton;
    
    bool aButton;
    bool bButton;
    bool xButton;
    bool yButton;
    
    bool selectButton;
    bool homeButton;
    bool startButton;
    
    //Shoulder buttons.
    bool lButton;
    bool rButton;
    bool zlButton;
    bool zrButton;
    int lButtonAnalog;
    int rButtonAnalog;
    
    //Analog sticks.
    int leftAnalogY;
    int leftAnalogX;
    
    int rightAnalogY;
    int rightAnalogX;
    
    void init();
    void update();
    
  private:
    
    uint8_t buttons[2];
    uint8_t values[4];
    
    boolean isPressed(byte p_row, byte p_bit);
    byte decoder(byte p_byte);
    
};
    

#endif
