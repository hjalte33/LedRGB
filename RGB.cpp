#include "Arduino.h"
#include "RGB.h"

RGB::RGB(int redPin, int greenPin, int bluePin){
  _pins[0] = redPin;
  _pins[1] = greenPin;
  _pins[2] = bluePin;
  for (int i; i < 3; i++){
    pinMode(_pins[i], OUTPUT); 
  }
}

void RGB::update(){
  for (int i; i < 3 ; i++){
    unsigned long col = (_color << (8*i)) & 0xFF0000 ;
    col = (col >> 16) * _brightness/255. ;
    analogWrite(_pins[i], col); 
  }
}

void RGB::set_mode(char mode){
  _mode = mode; 
}

void RGB::set_color(unsigned long color){
  _color = color;
}

void RGB::adjust_brightness(int amount){
   if (_brightness + amount < 0){
    _brightness = 0;
   }
  else if (_brightness + amount > 255){
    _brightness = 255 ;
  } 
  else{
    _brightness = _brightness + amount ; 
  }
}

void RGB::set_brightness(byte brightness){
  if (brightness < 0){
    _brightness = 0;
   }
  else if (brightness > 255){
    _brightness = 255 ;
  } 
  else{
    _brightness = brightness; 
  }
}
