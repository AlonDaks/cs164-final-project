
#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include "Led.h"
#include "Adafruit_WS2801.h"
#include "SPI.h"

class LedStrip : public ILed {
public:
	LedStrip(uint8_t numLeds, uint8_t dataPin, uint8_t clockPin);
	void begin();
	void setColor(uint8_t r, uint8_t g, uint8_t b) override;
private:
	uint8_t clockPin;
	uint8_t dataPin;
	uint8_t numLeds;
	Adafruit_WS2801 strip;

	uint32_t createColor(uint8_t r, uint8_t g, uint8_t b);
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

void LedStrip::setColor(uint8_t r, uint8_t g, uint8_t b) {
	for (int i = 0; i < strip.numPixels; ++i) {
		strip.setPixelColor(i, createColor(r, g, b));
	}
	strip.show();
}

uint32_t LedStrip::createColor(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

#endif