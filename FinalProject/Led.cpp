#include "Arduino.h"
#include "Led.h"
#include "stdint.h"
/*
 * 	Constructor.  Initializes the pins and the instance variables.
 */
Led::Led(int pin)
{
	this->pin = pin;
	pinMode(pin, OUTPUT);   
}

void Led::setValue(int value){
	if(value == 1){
		digitalWrite(pin, HIGH);
	} else{
		digitalWrite(pin, LOW);
	}
}