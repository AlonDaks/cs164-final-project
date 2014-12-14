/* AnimFunc.h
 * Base class for user-defined functions. 
 */

#ifndef LED_ANIM_ANIMFUNC_H
#define LED_ANIM_ANIMFUNC_H

#include <stdint.h>

struct AnimFunc {
	/* Returns whether this animation is over */
	virtual bool isOver(uint16_t elapsedTime) = 0;

	/* Called each tick to update the LEDs */
	virtual void update(uint16_t elapsedTime) = 0;
};

#endif