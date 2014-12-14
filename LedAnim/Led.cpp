#include "Led.h"
#include "Arduino.h"

#define MAX_INTENSITY 255
#define HALF_INTENSITY 127

/******************************
 * SimpleLed functions 
 ******************************/

SimpleLed::SimpleLed(uint8_t pin) : pin(pin), bIsAnalog(false) {
	pinMode(pin, OUTPUT);
}

SimpleLed::SimpleLed(uint8_t pin, bool isAnalog) : pin(pin), bIsAnalog(isAnalog) {
	pinMode(pin, OUTPUT);
}

void SimpleLed::setColor(Color& color) {
	if (bIsAnalog) {
		analogWrite(pin, color.red);
	} else if (color.red > HALF_INTENSITY) {
		digitalWrite(pin, HIGH);
	} else {
		digitalWrite(pin, LOW);
	}
}

/******************************
 * RgbLedCA functions 
 ******************************/

RgbLedCA::RgbLedCA(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t anodePin)
: redPin(rPin), greenPin(gPin), bluePin(bPin), anodePin(anodePin), brightness(MAX_INTENSITY) {
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);  
	pinMode(anodePin, OUTPUT); 
}

RgbLedCA::RgbLedCA(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t anodePin, bool isAnalog) 
: redPin(rPin), greenPin(gPin), bluePin(bPin), anodePin(anodePin) {
	brightness = isAnalog ? MAX_INTENSITY : 0;
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);  
	pinMode(anodePin, OUTPUT); 
}

RgbLedCA::RgbLedCA(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t anodePin, bool isAnalog, uint8_t brightness)
: redPin(rPin), greenPin(gPin), bluePin(bPin), anodePin(anodePin), brightness(brightness) {
	if (!isAnalog) {
		brightness = 0;
	}
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);  
	pinMode(anodePin, OUTPUT);
}

void RgbLedCA::setColor(Color& color) {
	if (brightness > 0) {
		analogWrite(anodePin, brightness);
		analogWrite(redPin, brightness - ((uint16_t) color.red * brightness)/MAX_INTENSITY);
		analogWrite(greenPin, brightness - ((uint16_t) color.green * brightness)/MAX_INTENSITY);
		analogWrite(bluePin, brightness - ((uint16_t) color.blue * brightness)/MAX_INTENSITY);
	} else {
		digitalWrite(anodePin, HIGH);
		digitalWrite(redPin, color.red > HALF_INTENSITY ? LOW : HIGH);
		digitalWrite(greenPin, color.green > HALF_INTENSITY ? LOW : HIGH);
		digitalWrite(bluePin, color.blue > HALF_INTENSITY ? LOW : HIGH);
	}
}


#undef MAX_INTENSITY
#undef HALF_INTENSITY