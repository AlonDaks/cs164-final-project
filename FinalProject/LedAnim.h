/* LedAnim.h
 * Defines LED Animations, which can be chained together to form complex sequences. 
 */

#ifndef LED_ANIM_H
#define LED_ANIM_H

#include "AnimFunc.h"

/* Defines type of LedAnim */
enum AnimType { ANIM_FUNC, ANIM_SEQ };

/* Base class for animations, which are linked lists that point to other animations. */
class LedAnim {
friend class SequencePlayer;
public:
	/* Returns the duration of this animation. */
	virtual uint16_t getDuration() = 0;

	/* Sets the animation that should be played after this animation. */
	void setNext(LedAnim& ledAnim);

	/* Removes links to any animations that play after this */
	void clearNext();
protected:
	LedAnim() : next(nullptr) {}
	AnimType type;
	LedAnim* next;
};

/* An animation driven by an update function */
class FnAnim : public LedAnim {
public:
	FnAnim(AnimFunc& d);
	uint16_t getDuration() override;
protected:
	AnimFunc& delegate;
};

/* An animation driven by a sequence of interpolatable values. */
class SeqAnim : public LedAnim {
public:
	SeqAnim();
	uint16_t getDuration() override;
protected:
	uint16_t duration;
	// TODO add reference to sequence
};

#endif