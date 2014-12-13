/* Led.h
 * Defines LED objects on which animations can be played.
 */

#ifndef LED_ANIM_LED_H
#define LED_ANIM_LED_H

#include "stdint.h"

/* Interface for LEDs */
class ILed {
public:
	virtual ~ILed() {}
    virtual void setColor(uint8_t r, uint8_t g, uint8_t b) = 0;
};

/* Defines a LED with R, G, and B channels */
class RgbLed : ILed {
public:
	RgbLed(uint8_t brightness, uint8_t cPin, uint8_t rPin, uint8_t gPin, uint8_t bPin);
	void setColor(uint8_t r, uint8_t g, uint8_t b) override;
protected:
	uint8_t brightness;		// value from 0 to 255, with 255 being brightest
	uint8_t cPin;			// cathode
	uint8_t rPin;	
	uint8_t gPin;
	uint8_t bPin;
};

#endif