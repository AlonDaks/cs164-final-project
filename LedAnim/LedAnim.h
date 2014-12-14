/* LedAnim.h
 * Defines LED Animations, which can be chained together to form complex sequences. 
 */

#ifndef LED_ANIM_H
#define LED_ANIM_H

#include <stdint.h>

struct AnimFunc {
	/* Returns whether this animation is over */
	virtual bool isOver(uint16_t elapsedTime) = 0;

	/* Called each tick to update the LEDs */
	virtual void update(uint16_t elapsedTime) = 0;
};

/* Base class for animations, which are linked lists that point to other animations. */
class LedAnim {
friend class AnimPlayer;
public:
	LedAnim(AnimFunc& f);

	/* Sets the animation that should be played after this animation. */
	void setNext(LedAnim& ledAnim);

	/* Removes links to any animations that play after this */
	void clearNext();
protected:
	//AnimType type;
	LedAnim* next;
	AnimFunc& func;
};

/* An animation driven by an update function */
/*class FnAnim : public LedAnim {
public:
	FnAnim(AnimFunc& d);
	uint16_t getDuration() override;
protected:
	AnimFunc& delegate;
};*/

/* An animation driven by a sequence of interpolatable values. */
/*class SeqAnim : public LedAnim {
public:
	SeqAnim();
	uint16_t getDuration() override;
protected:
	uint16_t duration;
	// TODO add reference to sequence
};*/

#endif