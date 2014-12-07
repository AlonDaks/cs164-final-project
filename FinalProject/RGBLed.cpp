#include "Arduino.h"
#include "RGBLed.h"
#include "Sequence.h"
#include "stdint.h"
/*
 * 	Constructor.  Initializes the pins and the instance variables.
 */
RGBLed::RGBLed(int red_pin, int green_pin, int blue_pin)
{
	this->red_pin = red_pin;
	this->green_pin = green_pin;
	this->blue_pin = blue_pin;
	pinMode(red_pin, OUTPUT); 
	pinMode(green_pin, OUTPUT); 
	pinMode(blue_pin, OUTPUT);   
}

void RGBLed::setValue(Color c) {
	analogWrite(red_pin, c.red);
	analogWrite(green_pin, c.green);
	analogWrite(blue_pin, c.blue);
}