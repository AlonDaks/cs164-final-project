/* AnimFunc.h
 * Base class for user-defined functions. 
 */

#ifndef LED_ANIM_ANIMFUNC_H
#define LED_ANIM_ANIMFUNC_H

#include <stdint.h>

class AnimFunc {
public:
	/* Returns the duration of this animation in milliseconds */
	virtual uint16_t durationInMillis() = 0;

	/* Called each tick to update the LEDs */
	virtual void update(uint16_t elapsedTime) = 0;
};

#endif