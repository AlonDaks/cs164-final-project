
#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <Adafruit_WS2801.h>
#include <SPI.h>
#include <Led.h>
#include <HashMap.h>

class LedStrip : public ILed {
public:
	LedStrip(uint8_t numLeds, uint8_t dataPin, uint8_t clockPin);
	void begin();
	void setColor(Color &color) override;
	void setColor(uint8_t addr, Color &color);
private:
	uint8_t clockPin;
	uint8_t dataPin;
	uint8_t numLeds;
	Adafruit_WS2801 strip;

	uint32_t createColor(Color &color);
};

LedStrip::LedStrip(uint8_t numLeds, uint8_t dataPin, uint8_t clockPin)
	: clockPin(clockPin), dataPin(dataPin), numLeds(numLeds) 
{
	strip = Adafruit_WS2801(numLeds, dataPin, clockPin);
}

void LedStrip::begin() {
	strip.begin();
	strip.show();
}

void LedStrip::setColor(Color &color) {
	for (int i = 0; i < strip.numPixels(); ++i) {
		strip.setPixelColor(i, createColor(color));
	}
	strip.show();
}

void LedStrip::setColor(uint8_t addr, Color &color) {
	strip.setPixelColor(addr, createColor(color));
	strip.show();
}

uint32_t LedStrip::createColor(Color &color) {
	uint32_t c;
	c = color.red;
	c <<= 8;
	c |= color.green;
	c <<= 8;
	c |= color.blue;
	return c;
}

#endif
