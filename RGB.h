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
        
        void set_color(byte red, byte green, byte blue, int luminance = -1);
        void set_color(byte color[], bool hasLuminance = false);
        void adjust_brightness(int amount);
        void set_brightness(byte brightness);
        
        void adjust_blinkSpeed(float amount);
        void adjust_noOfOldColors(float amount);
        
        void update(); 
        
  private:
        int _pins[3] ;
        
        //keeping track of colors
        const int brightness; // this is a constant and hold the index number of the brightness value
        byte _color [4] = {255, 0, 0, 255} ;// 3 colors and a brightness value 
        byte _oldColor[4] = {255,0,0,255};
        byte _oldColors[10][4]= {{255,0,0,255},{0,0,0,255},{255,0,255,255},
                                 {0,0,255,255},{0,255,255,255},{0,255,0,255},
                                 {255,255,0,255},{255,255,255,255},{127,127,127,255},{64,64,64,255},}; 
        byte _noOfOldColors = 2;
        byte _oldColorIndex = 0;
        
        //keeping track of modes
        int _mode;
        int _noOfModes = 3;
        
        // Other
        int _blinkSpeed = 1000;
        long _oldTime;
        byte _fadeCurve;
    
        // Private functions
        void blinking();
        void updateLed();
        void fadeing();
};

#endif

