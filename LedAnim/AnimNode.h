/* AnimNode.h
 * Defines LED Animations, which can be chained together to form complex sequences. 
 */

#ifndef LED_ANIM_ANIMNODE_H
#define LED_ANIM_ANIMNODE_H

#include <stdint.h>

extern uint32_t FOREVER;

class ILed;
class Sequence;

/* Defines a basic animation node. */
struct AnimNode {
	/* Returns whether this animation is over. By default  */
	virtual bool isOver(uint32_t elapsedMillis) = 0;

	/* Called each tick to update the LEDs */
	virtual void update(uint32_t elapsedMillis) = 0;

	/* Sets the animation that should be played after this animation. Returns the next animation for chaining */
	AnimNode& next(AnimNode& node);

	/* Removes links to any animations that play after this */
	void end();

	/* Returns the next animation that plays after this animation, or NULL if nonexistant. */
	AnimNode* next();
protected:
	AnimNode() : nextNode(nullptr) {}
	~AnimNode() {}
	AnimNode* nextNode;
};

/* AnimNode that executes the update function for a set amount of time. */
struct TimeNode : public AnimNode {
	TimeNode(uint32_t dur) : duration(dur) {}
	virtual bool isOver(uint32_t elapsedMillis) override;
protected:
	~TimeNode() {}
	uint32_t duration;
};

/* AnimNode that plays a particular sequence for a set number of repeats. */
struct SeqNode : public AnimNode {
	SeqNode(ILed& led, Sequence& seq, uint32_t numRepeats);
	virtual void update(uint32_t elapsedMillis) override;
	virtual bool isOver(uint32_t elapsedMillis) override;
protected:
	ILed& led;
	Sequence& sequence;
	uint32_t numRepeats;
	uint32_t curRepeats;
};

#endif