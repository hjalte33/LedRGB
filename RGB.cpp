/*
  RGB.h - Library for controlling an rgb led. 
  It has multiple modes.
  It only updates when the update function is runned.
  Created by Hjalte Nielsen 12 2016.
  Github: https://github.com/hjalte33/ledRemote.git
  Demo video on https://youtu.be/jiGEJYM5Z0I
*/

#include "Arduino.h"
#include "RGB.h"



//constructer
RGB::RGB(int redPin, int greenPin, int bluePin)
: brightness(3)// define the array index that is the brightness
{
  _pins[0] = redPin;
  _pins[1] = greenPin;
  _pins[2] = bluePin;
  for (int i; i < 3; i++){
    pinMode(_pins[i], OUTPUT); 
  }
}

// update function that needs to be executed constrantly to update the Led
void RGB::update(){
  switch (_mode){
    case 0 :
      updateLed();
      delay(10);
      break;
    case 1 :
      blinking();
      break;
    case 2 :
      fadeing();  
    default:
      updateLed();
      break;
    } 
}


// set the outputpins to the desired color. 
void RGB::updateLed(){
  for (int i=0; i < 3 ; i++){
    analogWrite(_pins[i], _color[i]*_color[brightness]/255.); 
  }
}


// toggle the mode by the interval variable "change"
void RGB::toggle_mode(int change){
  // remember the old color
  memcpy(_oldColor, _color, 4) ;   
  // check if we exeede the allowed modes. 
  if (_mode + change + 1 > _noOfModes){
    _mode = 0;    
  }
  else if (_mode + change < 0 ){
    _mode = (_noOfModes - 1);
  }
  else{
    _mode += change;
  }
  set_color(0,0,0);
  delay(250);
  //blink the number of modes
  for (int i=0; i < _mode + 1; i++){ 
    set_color(255,255,255,255);
    delay(250);
    set_color(0,0,0,0);
    delay(250); 
  }
  delay(300);
  // set color back to what it was before.
  memcpy(_color, _oldColor, 4);
  updateLed();
}


// Just set a color 
void RGB::set_color(byte red, byte green, byte blue, int luminance){
  _color[0] = red;
  _color[1] = green;
  _color[2] = blue;
  if (luminance >= 0 && luminance <= 255){
    _color[3] = luminance;
  }  
  updateLed();
}

// just set a color with an array 
void RGB::set_color(byte color[], bool hasLuminance){
  if (hasLuminance){
    memcpy(_color, color, 4); 
  }
  else{
    memcpy(_color, color, 3);
  } 
  updateLed();
}

// adjust the global brightness by a sutain amount.
void RGB::adjust_brightness(int amount){
   if (_color[brightness] + amount < 1){
    _color[brightness] = 1;
   }
  else if (_color[brightness] + amount > 255){
    _color[brightness] = 255 ;
  } 
  else{
    _color[brightness] = _color[brightness] + amount ; 
  }
}


// set a specific brightness 
void RGB::set_brightness(byte newBrightness){
  if (newBrightness < 0){
    _color[brightness] = 0;
   }
  else if (newBrightness > 255){
    _color[brightness] = 255 ;
  } 
  else{
    _color[brightness] = newBrightness; 
  }
}



// blink the Led between two or up to 10 different colors a sutain interval 
void RGB::blinking(){
  if (_oldTime + _blinkSpeed < millis()){    
    if (_oldColorIndex < _noOfOldColors - 1){
      memcpy(_oldColors[_oldColorIndex], _color, 4);
      _oldColorIndex ++ ;
      set_color(_oldColors[_oldColorIndex], true);
    }
    else{
      memcpy(_oldColors[_oldColorIndex], _color, 4);
      _oldColorIndex = 0 ;
      set_color(_oldColors[_oldColorIndex], true);
    }
    _oldTime = millis();  
  } 
  else{
    updateLed();
    delay(10); 
  }
}


//addjust the blink speed with a sutain amount
void RGB::adjust_noOfOldColors(float amount){
   if (_noOfOldColors + amount < 2){
    _noOfOldColors = 2;  // remember that we count from 0 so this is 2 colors.
   }
  else if (_noOfOldColors + amount > 10){
    _noOfOldColors = 10 ;
  } 
  else{
    _noOfOldColors = _noOfOldColors + amount ; 
  }
 delay(500);
}





//addjust the blink speed with a sutain amount
void RGB::adjust_blinkSpeed(float amount){
   if (_blinkSpeed + amount < 10){
    _blinkSpeed = 10;
   }
  else if (_blinkSpeed + amount > 5000){
    _blinkSpeed = 5000 ;
  } 
  else{
    _blinkSpeed = _blinkSpeed + amount ; 
  }
 
}


// fade the led at the colors specifyed in the blining mode. 
void RGB::fadeing(){
  if ( millis() > _oldTime + _blinkSpeed/100.){
        if (_fadeCurve == 255){
          _fadeCurve = 0;
          if(_oldColorIndex + 1 == _noOfOldColors){ 
            _oldColorIndex = 0;
          }
          else{
            _oldColorIndex ++;
          }
        }
        else{
          _fadeCurve ++; 
        }    
        byte newColor [4] ;
        if (_oldColorIndex + 1 < _noOfOldColors){
          for (int i = 0; i < 4; i++){
              newColor[i] = ((255 - _fadeCurve)/255.) * _oldColors[_oldColorIndex][i] + (_fadeCurve/255.)* _oldColors[_oldColorIndex + 1][i] ;
          } 
        }
        else{
          for (int i = 0; i < 4; i++){
              newColor[i] = ((255 - _fadeCurve)/255.) * _oldColors[_oldColorIndex][i] + (_fadeCurve/255.)* _oldColors[0][i] ;
          }
        }
        set_color(newColor, true);
        _oldTime = millis();
  }
  
}


