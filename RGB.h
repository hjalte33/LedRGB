/*
  RGB.h - Library for controlling an rgb led. 
  It has multiple modes.
  It only updates when the update function is runned.
  Created by Hjalte Nielsen 12 2016.
  Github: https://github.com/hjalte33/ledRemote.git
*/

#ifndef RGB_h
#define RGB_h

#include "Arduino.h"


 
class RGB
{
  public:
    RGB(int redPin, int greenPin, int bluePin);
    void set_mode(char mode);
    void set_color(unsigned long color);
    void adjust_brightness(int amount);
    void set_brightness(byte brightness);
    void update(); 
    
  private:
    int _pins[3] ;
    char _mode = 's';
    unsigned long _color = 0xFF0000 ;
    byte _brightness = 255 ;  
};

#endif

