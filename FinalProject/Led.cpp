#include "Led.h"

Led::Led(int pin)
{
	this->pin = pin;
	pinMode(pin, OUTPUT);   
}

void Led::setValue(uint8_t value){
	if(value == 1){
		digitalWrite(pin, HIGH);
	} else{
		digitalWrite(pin, LOW);
	}
}