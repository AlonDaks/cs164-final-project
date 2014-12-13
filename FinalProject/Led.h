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
    virtual void setColor(uint8_t r, uint8_t g, uint8_t, b) = 0;
};

/* Defines a LED with R, G, and B channels */
class RgbLed : ILed {
public:
	
protected:
	uint8_t rPin;
	uint8_t gPin;
	uint8_t bPin;
};

#endif