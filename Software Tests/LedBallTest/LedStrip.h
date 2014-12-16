
#ifndef LEDSTRIP_H
#define LEDSTRIP_H

// In main .ino file, include the following headers:
// #include <Adafruit_WS2801.h>
// #include <SPI.h>
// #include <LedAnim.h>
// #include "LedStrip.h"

class LedStrip;

class StripLights : public ILed {
public:
        StripLights() {}
		StripLights(uint8_t id, LedStrip* parent) : id(id), parent(parent) { }

        void dummy() {
          Serial.println("asdf");
        }
	void setColor(const Color& color) override;

public:
	uint8_t id;
	LedStrip* parent;
};

class LedStrip : public ILed {
public:
	LedStrip(uint8_t numLeds, uint8_t dataPin, uint8_t clockPin, uint8_t brightness);
	~LedStrip();

	void setColor(const Color &color) override;
	void setColor(uint8_t addr, const Color &color);
	void setColor(const int* arr, size_t n, const Color &color);
	uint16_t size();

	Array<ILed*>& getLights();

    void selfTest();

private:
	uint8_t clockPin;
	uint8_t dataPin;
	uint8_t brightness;
	Adafruit_WS2801 strip;
    StripLights* ls;
	Array<ILed*> lights;

	uint32_t createColor(const Color &color);
};

void StripLights::setColor(const Color &color) {
	parent->setColor(id, color);
}

LedStrip::LedStrip(uint8_t numLeds, uint8_t dataPin, uint8_t clockPin, uint8_t brightness)
: clockPin(clockPin), dataPin(dataPin), brightness(brightness) 
{
	strip = Adafruit_WS2801(numLeds, dataPin, clockPin);
    strip.begin();
    strip.show();
    ls = new StripLights[numLeds]; 
  	for (int i = 0; i < strip.numPixels(); ++i) {
        ls[i].id = i;
        ls[i].parent = this;
		lights.append(&ls[i]);
	}
}

LedStrip::~LedStrip() {
	delete[] ls;
}

uint16_t LedStrip::LedStrip::size() {
	return strip.numPixels();
}

void LedStrip::selfTest() {
    for (int i = 0; i < strip.numPixels(); ++i) {
        Serial.println(i);
        lights.get(i)->setColor(BLUE);
	} 
}

void LedStrip::setColor(const Color &color) {
	for (int i = 0; i < strip.numPixels(); ++i) {
		strip.setPixelColor(i, color.toInt(brightness));
	}
	strip.show();
}

void LedStrip::setColor(uint8_t addr, const Color &color) {
	if (addr < strip.numPixels()) {
		strip.setPixelColor(addr, color.toInt(brightness));
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
	return lights;
}

#endif
