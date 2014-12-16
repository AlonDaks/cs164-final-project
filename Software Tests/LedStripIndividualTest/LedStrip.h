
#ifndef LEDSTRIP_H
#define LEDSTRIP_H

// In main .ino file, include the following headers:
// #include <Adafruit_WS2801.h>
// #include <SPI.h>
// #include <LedAnim.h>
// #include "LedStrip.h"

class StripLights;

class LedStrip : public ILed {
public:
	LedStrip(uint8_t numLeds, uint8_t dataPin, uint8_t clockPin, uint8_t brightness);
	~LedStrip();

	void begin();

	void setColor(const Color &color) override;
	void setColor(uint8_t addr, const Color &color);
	void setColor(const int* arr, size_t n, const Color &color);

	Array<ILed*>& getLights();

private:
	uint8_t clockPin;
	uint8_t dataPin;
	uint8_t brightness;
	Adafruit_WS2801 strip;
	StripLights* lights;
	Array<ILed*> arr;

	uint32_t createColor(const Color &color);
};

class StripLights : public ILed {
public:
	StripLights(uint8_t id, LedStrip* parent) : id(id), parent(parent) {}

	void setColor(const Color &color) override {
		parent->setColor(id, color);
	}

private:
	uint8_t id;
	LedStrip* parent;
};

LedStrip::LedStrip(uint8_t numLeds, uint8_t dataPin, uint8_t clockPin, uint8_t brightness)
: clockPin(clockPin), dataPin(dataPin), brightness(brightness) 
{
	strip = Adafruit_WS2801(numLeds, dataPin, clockPin);
	lights = (StripLights*) malloc(sizeof(StripLights) * numLeds);
	if (!lights) {
		exit(1);
	}
	for (int i = 0; i < numLeds; ++i) {
		lights[i] = StripLights(i, this);
		arr.append(lights[i]);
	}
}

LedStrip::~LedStrip() {
	free(lights);
}

void LedStrip::begin() {
	strip.begin();
	strip.show();
}

void LedStrip::setColor(const Color &color) {
	for (int i = 0; i < strip.numPixels(); ++i) {
		strip.setPixelColor(i, color.toInt());
	}
	strip.show();
}

void LedStrip::setColor(uint8_t addr, const Color &color) {
	if (addr < strip.numPixels()) {
		strip.setPixelColor(addr, color.toInt());
		strip.show();
	}
}

void LedStrip::setColor(const int* arr, size_t n, const Color &color) {
	uint32_t c = createColor(color);
	for (int i = 0; i < n; ++i) {
		if (arr[i] >= 0 && arr[i] < strip.numPixels()) {
			strip.setPixelColor(arr[i], c);
		}
	}
	strip.show();
}

Array<ILed*>& LedStrip::getLights() {
	return arr;
}

#endif
