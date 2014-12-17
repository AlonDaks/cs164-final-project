/*
 * ButtonTest - modification of Button tutorial
 */

#include "PushButton.h"

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 14;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

PushButton pb = PushButton(buttonPin, 2000);  // wait 2 sec before lighting up

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);    
}

void loop(){
  Serial.println(digitalRead(buttonPin));
  delay(1000);
  pb.update();

  if (pb.isPressed()) {       
    digitalWrite(ledPin, HIGH);
    delay(1000);
  } else {
    digitalWrite(ledPin, LOW); 
  }
}
