/*
  RGB.h - Library for controlling an rgb led. 
  It has multiple modes.
  It only updates when the update function is runned.
  Created by Hjalte Nielsen 12 2016.
  Github: https://github.com/hjalte33/ledRemote.git
  Demo video on https://youtu.be/jiGEJYM5Z0I
*/


#ifndef RGB_h
#define RGB_h
#include "Arduino.h"


class RGB
{
  public:
    RGB(int redPin, int greenPin, int bluePin);
    void toggle_mode(int change);
    void set_color(unsigned long color);
    void adjust_brightness(int amount);
    void set_brightness(byte brightness);
    void adjust_blink_speed(float amount);
    void update(); 
    
  private:
    int _pins[3] ;
    unsigned long _color = 0xFF0000 ;
    byte _brightness = 255 ; 
    long _oldTime;
    unsigned long _oldColor; 
    int _mode;
    int _noOfModes = 3;
    int _blink_speed = 1000;
    // Functions
    void blinking();
    void updateLed();
    void fadeing();
};

#endif

