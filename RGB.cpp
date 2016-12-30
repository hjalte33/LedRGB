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
RGB::RGB(int redPin, int greenPin, int bluePin){
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
      break;
    default:
      updateLed();
      break;
    } 
}

// set the outputpins to the desired color. 
void RGB::updateLed(){
  for (int i; i < 3 ; i++){
    unsigned long col = (_color << (8*i)) & 0xFF0000 ;
    col = (col >> 16) * _brightness/255. ;
    analogWrite(_pins[i], col); 
  }
}


// toggle the mode by the interval variable "change"
void RGB::toggle_mode(int change){
  // remember the current color 
  unsigned long colorBefore = _color;
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
  //blink the number of modes
  _color = 0x000000;
  updateLed();
  delay(250);
  for (int i; i < _mode + 1; i++){ 
    _color = 0xFFFFFF;
    updateLed();
    delay(250);
    _color = 0x000000;
    updateLed();
    delay(250); 
  }
  delay(300);
  // set color back to what it was before.
  _color = colorBefore;
  updateLed();
}


// Just set a color 
void RGB::set_color(unsigned long color){
  _color = color;
  updateLed();
}

// adjust the global brightness by a sutain amount.
void RGB::adjust_brightness(int amount){
   if (_brightness + amount < 1){
    _brightness = 1;
   }
  else if (_brightness + amount > 255){
    _brightness = 255 ;
  } 
  else{
    _brightness = _brightness + amount ; 
  }
}


// set a specific brightness 
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

// blink the Led with a sutain interval 
void RGB::blinking(){
  if (_oldTime + _blink_speed < millis()){
    if (_color == 0x000000){
      _color = _oldColor;
      updateLed();
    }
    else{ 
      _oldColor = _color;
      _color = 0x000000;
      updateLed();    
    }
    _oldTime = millis();
    
  }  
}

//addjust the blink speed with a sutain amount
void RGB::adjust_blink_speed(float amount){
   if (_blink_speed + amount < 100){
    _blink_speed = 100;
   }
  else if (_blink_speed + amount > 3000){
    _blink_speed = 3000 ;
  } 
  else{
    _blink_speed = _blink_speed + amount ; 
  }
 
}


// fade the led at random colors at a random phase. 
void RGB::fadeing(){

  _color = 0x000000;
  for (int i; i < 3; i++){
    long var = (sin(millis()*0.0005 + i*(sin(millis()*0.00001))*3.14) * 127) ; //secret fade fuction I created ;)
    _color += ((long(var+127))<< i*8); 
  }
  
  updateLed();
}


