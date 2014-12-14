#include "Led.h"
#include "Arduino.h"

RgbLed::RgbLed(uint8_t brightness, uint8_t cPin, uint8_t rPin, uint8_t gPin, uint8_t bPin)
	: brightness(brightness), cPin(cPin), rPin(rPin), gPin(gPin), bPin(bPin)
{
	pinMode(cPin, OUTPUT);
	pinMode(rPin, OUTPUT);
	pinMode(gPin, OUTPUT);
	pinMode(bPin, OUTPUT);   
}

void RgbLed::setColor(Color& color) {
	analogWrite(cPin, brightness);
	analogWrite(rPin, brightness - ((uint16_t) color.red * brightness)/0xFF);
	analogWrite(gPin, brightness - ((uint16_t) color.green * brightness)/0xFF);
	analogWrite(bPin, brightness - ((uint16_t) color.blue * brightness)/0xFF);
}