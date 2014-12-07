#include "Arduino.h"
#include "Sequence.h"
/*
 * 	Constructor.  Initializes the pins and the instance variables.
 */
Sequence::Sequence(int _pin)
{
	// Define pins for the LED display:
	this->pin = _pin;    
	pinMode(pin, OUTPUT);     	
}

void Sequence::blink(){
	digitalWrite(pin, LOW);
    delay(1000);
    digitalWrite(pin, HIGH);
    delay(1000);
}