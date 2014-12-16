/* AnimNode.h
 * Defines LED Animations, which can be chained together to form complex sequences. 
 */

#ifndef LED_ANIM_ANIMNODE_H
#define LED_ANIM_ANIMNODE_H

#include <stdint.h>
#include "Array.h"

extern const uint32_t FOREVER;

class ILed;
class Sequence;

/* Defines a basic animation node. */
struct AnimNode {
	/* Called each tick to update the LEDs */
	virtual void update(uint32_t elapsedMillis) = 0;

	/* Returns whether this animation is over. By default  */
	virtual bool isOver(uint32_t elapsedMillis) = 0;

	/* Sets the animation that should be played after this animation. Returns the next animation for chaining */
	AnimNode& next(AnimNode& node);

	/* Removes links to any animations that play after this */
	void end();

	/* Returns the next animation that plays after this animation, or NULL if nonexistant. */
	virtual AnimNode* next();
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

/* AnimNode that repeats for a set amount of times. */
struct RepNode : public AnimNode {
	virtual bool isRepOver(uint32_t elapsedMillis) = 0;
	virtual bool isOver(uint32_t elapsedMillis) override;
protected:
	RepNode(uint32_t numRepeats);
	uint32_t numRepeats;
	uint32_t curRepeats;
};

/* AnimNode that plays a particular sequence for a set number of repeats. */
struct SeqNode : public RepNode {
	SeqNode(ILed& led, Sequence& seq);
	SeqNode(ILed& led, Sequence& seq, uint32_t numRepeats);
	virtual void update(uint32_t elapsedMillis) override;
	virtual bool isRepOver(uint32_t elapsedMillis) override;
protected:
	ILed& led;
	Sequence& sequence;
};

/* AnimNode that blends multiple sequences together. Length of the node is the length of the longest sequence */
struct BlendNode : public RepNode {
	BlendNode(ILed& led, Array<Sequence*>& seq, float* weights);
	BlendNode(ILed& led, Array<Sequence*>& seq, float* weights, uint32_t numRepeats);
	virtual void update(uint32_t elapsedMillis) override;
	virtual bool isRepOver(uint32_t elapsedMillis) override;
protected:
	ILed& led;
	Array<Sequence*>& sequences;
	float* weights;
	uint32_t length;
};

/* AnimNode that plays a particular sequence on an array of LEDs, each offset by some amount. */
struct DelayNode : public RepNode {
	DelayNode(Array<ILed*>& leds, Sequence& seq, unsigned int (*offsetFunc) (int));
	DelayNode(Array<ILed*>& leds, Sequence& seq, unsigned int (*offsetFunc) (int), uint32_t numRepeats);
	~DelayNode();
	virtual void update(uint32_t elapsedMillis) override;
	virtual bool isRepOver(uint32_t elapsedMillis) override;
	uint32_t totalDuration();
protected:
	Array<ILed*>& leds;
	Sequence& sequence;
	uint32_t maxOffset;
	uint32_t* offsets;
};

/* An AnimNode that plays multiple */
/*struct MultiNode : public AnimNode {
	MultiNode(Array<AnimNode*>& nodes);
	virtual void update(uint32_t elapsedMillis) override;
protected:
	Array<AnimNode*>& animNodes;
};*/

#endif