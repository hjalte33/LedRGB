
#include <IRremote.h>
#include <Arduino.h>
#include "datastructures.h"

decode_results signals;

int recvPin = 3;
IRrecv irrecv(recvPin);

int redPin = 6;
int greenPin = 10;
int bluePin = 9;



void updateLed (RGB* led) {
  analogWrite(redPin,   led->red  *(led->brightness/255.));
  analogWrite(greenPin, led->green*(led->brightness/255.));
  analogWrite(bluePin,  led->blue *(led->brightness/255.));
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(115200);
  irrecv.enableIRIn(); // enable input from IR receiver
  
}
 
RGB myLed;
void loop() {
 
  updateLed(&myLed);
  while (myLed.brightness > 0){
    myLed.brightness --;
    updateLed(&myLed);
    Serial.print(myLed.brightness);
    Serial.print("\n");
    delay(10); 
  }
  while (myLed.brightness < 255){
    myLed.brightness ++ ;
    updateLed(&myLed);
    Serial.print(myLed.brightness);
    Serial.print("\n");
    delay(10);
  } 
    
}


