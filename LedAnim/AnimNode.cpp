#include "AnimNode.h"
#include "Led.h"
#include "Sequence.h"

uint32_t FOREVER = 4294967295;

/******************************
 * AnimNode functions 
 ******************************/
AnimNode& AnimNode::next(AnimNode& node) {
	nextNode = &node;
	return node;
}

void AnimNode::end() {
	nextNode = nullptr;
}

AnimNode* AnimNode::next() {
	return nextNode;
}

/******************************
 * TimeNode functions 
 ******************************/

bool TimeNode::isOver(uint32_t elapsedMillis) { 
	if (duration == FOREVER) {
		return false;
	} else {
		return elapsedMillis > duration; 
	}
}

/******************************
 * SeqNode functions 
 ******************************/

SeqNode::SeqNode(ILed& led, Sequence& seq, uint32_t numRepeats) 
	: led(led), sequence(seq), numRepeats(numRepeats), curRepeats(0) { }


void SeqNode::update(uint32_t elapsedMillis) {
	Sequence::apply(elapsedMillis, sequence, led);
}

bool SeqNode::isOver(uint32_t elapsedMillis) {
	if (numRepeats == FOREVER) {
		return false;
	} else {
		if (sequence.getDuration() * (curRepeats + 1) < elapsedMillis) {
			curRepeats++;
		}
		return curRepeats > numRepeats; 
	}
}

/******************************
 * OffsetNode functions 
 ******************************/

OffsetNode::OffsetNode(ILedArray leds, Sequence& seq, uint32_t (*offsetFunc) (uint16_t)) 
	: leds(leds), sequence(seq), offsetFunc(offsetFunc) { 
		maxOffset = 0;
		for(int i = 0; i < leds.size(); i++){
			uint32_t currOffset = offsetFunc(i);
			if(currOffset > maxOffset) {
				maxOffset = currOffset;
			}
		}
	}


void OffsetNode::update(uint32_t elapsedMillis) {
	for(int i = 0; i < leds.size(); i++){
		if(elapsedMillis > offsetFunc(i)){
			Sequence::apply(elapsedMillis, sequence, leds.get(i));
		}
	}
}

bool OffsetNode::isOver(uint32_t elapsedMillis) {
	return sequence.getDuration() + maxOffset > elapsedMillis;
}
