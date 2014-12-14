/* Led.h
 * Defines LED objects on which animations can be played.
 */

#ifndef LED_ANIM_LED_H
#define LED_ANIM_LED_H

#include "stdint.h"
#include "Color.h"

/* Interface for LEDs */
class ILed {
public:
    virtual void setColor(Color& color) = 0;
protected:
	~ILed() {}
};

/* Defines a single-color LED. Intensity is only specified through the red channel. */
class SimpleLed : public ILed {
public:
	/* Uses digital write */
	SimpleLed(uint8_t pin);

	/* Digital or analog write */
	SimpleLed(uint8_t pin, bool isAnalog);

	virtual void setColor(Color& color) override;
protected:
	uint8_t pin : 6;
	uint8_t bIsAnalog : 1;
};

/* Defines a common-anode LED with red, green, and blue channels */
class RgbLedCA : public ILed {
public:
	RgbLedCA(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t anodePin);

	RgbLedCA(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t anodePin, bool isAnalog);

	RgbLedCA(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t anodePin, bool isAnalog, uint8_t brightness);

	virtual void setColor(Color& color) override;
protected:
	uint32_t redPin : 6;
	uint32_t greenPin : 6;
	uint32_t bluePin : 6;
	uint32_t anodePin : 6;
	uint32_t brightness : 8;	// 0 = digital, 1-255 = brighness 
};

#endif