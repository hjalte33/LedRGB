/*
  Remotecontrolled RGB diode
  Requileh libraries # IRremote Arduino Library fourd on http://z3t0.github.io/Arduino-IRremote/
  It uses the RGB class found in RGB.h
  
  Created by Hjalte Nielsen 12 2016.
  Github: https://github.com/hjalte33/ledRemote.git
  Demo video on https://youtu.be/jiGEJYM5Z0I
*/


#include <IRremote.h>
#include <Arduino.h>
#include "RGB.h"

int recvPin = 3;
IRrecv irrecv(recvPin);
decode_results signals;
decode_results lastSignal;

int redPin = 6;
int greenPin = 10;
int bluePin = 9;

// Object of the RGB class. see RGB.h and RGB.cpp for further info.
// The numbers are pin numbers for red green and blue.
RGB myLed(6, 10, 9) ;



void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); // enable input from IR receiver
  myLed.update(); // let there be light from the beginning 
}

// Look at the receved remote control signal and decide what to do.
void translateIR(){
  switch(signals.value){

    case 0xFFA25D:{  
      Serial.println(" CH-            "); 
      myLed.adjust_noOfOldColors(-1);
      break;
    }
    case 0xFF629D:{  
      Serial.println(" CH             "); 
      break;
    }
    case 0xFFE21D: { 
      Serial.println(" CH+            "); 
      myLed.adjust_noOfOldColors(1);
      break;
    }
    case 0xFF22DD:{  
      Serial.println(" PREV           "); 
      myLed.toggle_mode(-1); 
      break;
    }
    case 0xFF02FD:{  
      Serial.println(" NEXT           ");
      myLed.toggle_mode(1); 
      break;
    }
    case 0xFFC23D:{  
      Serial.println(" PLAY/PAUSE     "); 
      break;
    }
    case 0xFFE01F:{  
      Serial.println(" VOL-           "); 
      myLed.adjust_brightness(-10);
      break;
    }
    case 0xFFA857: {
      Serial.println(" VOL+           "); 
      myLed.adjust_brightness(10);
      break;
    }
    case 0xFF906F:{  
      Serial.println(" EQ             "); 
      break;
    }
    case 0xFF6897:{  
      Serial.println(" 0              ");
      myLed.set_brightness(255); 
      break;
    }
    case 0xFF9867:{ 
      Serial.println(" 100+           "); 
      myLed.adjust_blinkSpeed(-10);
      break;
    }
    case 0xFFB04F:{  
      Serial.println(" 200+           "); 
      myLed.adjust_blinkSpeed(10);
      break;
    }
    case 0xFF30CF:{  
      Serial.println(" 1              ");
      myLed.set_color(255,0,0);
      break;
    }
    case 0xFF18E7: {
      Serial.println(" 2              "); 
     
      myLed.set_color(0,255,0);
      break;
    }
    case 0xFF7A85:{  
      Serial.println(" 3              "); 
      myLed.set_color(0,0,255);
      break;
    }
    case 0xFF10EF: { 
      Serial.println(" 4              "); 
      myLed.set_color(255,255,0);
      break;
    }
    case 0xFF38C7:{  
      Serial.println(" 5              "); 
      myLed.set_color(255,0,255);
      break;
    }
    case 0xFF5AA5:{  
      Serial.println(" 6              "); 
      myLed.set_color(0,255,255);
      break;
    }
    case 0xFF42BD:{  
      Serial.println(" 7              "); 
      myLed.set_color(255,127,0);
      break;
    }
    case 0xFF4AB5:{  
      Serial.println(" 8              "); 
      myLed.set_color(255,255,255);
      break;
    }
    case 0xFF52AD:{  
      Serial.println(" 9              "); 
      myLed.set_color(0,0,0);
      break;
    }
    case 0xFFFFFFFF:{  
      Serial.println(" Repeat         ");
      delay(50);
      signals = lastSignal ;
      translateIR();
      break;
    }
    default: 
      Serial.println(" other button   ");
      Serial.print(signals.value, HEX);
  }
  lastSignal = signals;
  myLed.update();
}

// listen for remote signal and update the led. 
void loop() {
  if (irrecv.decode(&signals)){ // have we received an IR signal?
    translateIR();
    irrecv.resume();
  } 
  myLed.update();

}


