
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

RGB myLed(6, 10, 9) ;


void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn(); // enable input from IR receiver
  myLed.update();

}

void translateIR(){
  switch(signals.value){

    case 0xFFA25D:  
      Serial.println(" CH-            "); 
      break;
  
    case 0xFF629D:  
      Serial.println(" CH             "); 
      break;
  
    case 0xFFE21D:  
      Serial.println(" CH+            "); 
      break;
  
    case 0xFF22DD:  
      Serial.println(" PREV           "); 
      break;
  
    case 0xFF02FD:  
      Serial.println(" NEXT           "); 
      break;
  
    case 0xFFC23D:  
      Serial.println(" PLAY/PAUSE     "); 
      break;
  
    case 0xFFE01F:  
      Serial.println(" VOL-           "); 
      myLed.adjust_brightness(-10);
      break;
  
    case 0xFFA857:  
      Serial.println(" VOL+           "); 
      myLed.adjust_brightness(10);
      break;
  
    case 0xFF906F:  
      Serial.println(" EQ             "); 
      break;
  
    case 0xFF6897:  
      Serial.println(" 0              ");
//      myLed.brightness = 255; 
      break;
  
    case 0xFF9867:  
      Serial.println(" 100+           "); 
      break;
  
    case 0xFFB04F:  
      Serial.println(" 200+           "); 
      break;
  
    case 0xFF30CF:  
      Serial.println(" 1              "); 
      break;
  
    case 0xFF18E7:  
      Serial.println(" 2              "); 
      break;
  
    case 0xFF7A85:  
      Serial.println(" 3              "); 
      break;
  
    case 0xFF10EF:  
      Serial.println(" 4              "); 
      break;
  
    case 0xFF38C7:  
      Serial.println(" 5              "); 
      break;
  
    case 0xFF5AA5:  
      Serial.println(" 6              "); 
      break;
  
    case 0xFF42BD:  
      Serial.println(" 7              "); 
      break;
  
    case 0xFF4AB5:  
      Serial.println(" 8              "); 
      break;
  
    case 0xFF52AD:  
      Serial.println(" 9              "); 
      break;
    
    case 0xFFFFFFFF:  
      Serial.println(" Repeat         ");
      signals = lastSignal ;
      delay(100);
      translateIR();
      break;
    
    default: 
      Serial.println(" other button   ");
      Serial.print(signals.value, HEX);
  }
  lastSignal = signals;
  delay(10);
}

void loop() {
  if (irrecv.decode(&signals)){ // have we received an IR signal?
    translateIR();
    myLed.update();
    irrecv.resume();
  } 
    
}


