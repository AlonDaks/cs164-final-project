#include "AnimNode.h"
#include "Led.h"
#include "Sequence.h"

const uint32_t FOREVER = 4294967295;

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
 * RepNode functions 
 ******************************/

RepNode::RepNode(uint32_t numRepeats) 
: numRepeats(numRepeats), curRepeats(0) {}

bool RepNode::isOver(uint32_t elapsedMillis) {
	if (isRepOver(elapsedMillis)) {
		curRepeats++;
		return true;
	} else {
		return false;
	}
}

AnimNode* RepNode::next() {
	if (numRepeats == FOREVER || curRepeats <= numRepeats) {
		return this;
	} else {
		return nextNode;
	}
}

/******************************
 * SeqNode functions 
 ******************************/

SeqNode::SeqNode(ILed& led, Sequence& seq) : SeqNode(led, seq, 0) {}

SeqNode::SeqNode(ILed& led, Sequence& seq, uint32_t numRepeats) 
: RepNode(numRepeats), led(led), sequence(seq) {}

void SeqNode::update(uint32_t elapsedMillis) {
	Sequence::apply(elapsedMillis, sequence, led);
}

bool SeqNode::isRepOver(uint32_t elapsedMillis) {
	return elapsedMillis > sequence.getDuration();
}

/******************************
 * BlendNode functions 
 ******************************/

BlendNode::BlendNode(ILed& led, Array<Sequence*>& seq, float* weights)
 : BlendNode(led, seq, weights, 0) {}

BlendNode::BlendNode(ILed& led, Array<Sequence*>& seq, float* weights, uint32_t numRepeats)
: RepNode(numRepeats), led(led), sequences(seq), weights(weights), length(0) {
	float totalWeight = 0;
	for (int i = 0; i < sequences.size(); ++i) {
		totalWeight += weights[i];
		uint32_t len = sequences.get(i)->getDuration();
		if (len > length) {
			length = len;
		}
	}
	for (int i = 0; i < sequences.size(); ++i) {
		weights[i] /= totalWeight;			// normalize the weights
	}
}

void BlendNode::update(uint32_t elapsedMillis) {
	float rawRed = 0;
	float rawGreen = 0;
	float rawBlue = 0;
	Color color;
	for (int i = 0; i < sequences.size(); ++i) {
		float weight = weights[i];
		Sequence::update(elapsedMillis, *sequences.get(i), color);
		rawRed += weight * color.red;
		rawGreen += weight * color.green;
		rawBlue += weight * color.blue;
	}
	color.red = (uint8_t) (rawRed + 0.5);
	color.green = (uint8_t) (rawGreen + 0.5);
	color.blue = (uint8_t) (rawBlue + 0.5);
	led.setColor(color);
}

bool BlendNode::isRepOver(uint32_t elapsedMillis) {
	return elapsedMillis > length;
}

/******************************
 * DelayNode functions 
 ******************************/

DelayNode::DelayNode(Array<ILed*>& leds, Sequence& seq, uint32_t (*offsetFunc) (uint16_t))
: DelayNode(leds, seq, offsetFunc, numRepeats) {}

DelayNode::DelayNode(Array<ILed*>& leds, Sequence& seq, uint32_t (*offsetFunc) (uint16_t), uint32_t numRepeats) 
: RepNode(numRepeats), leds(leds), sequence(seq), maxOffset(0) {
	offsets = (uint32_t*) malloc(sizeof(uint32_t) * leds.size());
	for(int i = 0; i < leds.size(); i++) {
		uint32_t currOffset = offsetFunc(i);
		offsets[i] = currOffset;
		if(currOffset > maxOffset) {
			maxOffset = currOffset;
		}
	}
}

DelayNode::~DelayNode() {
	free(offsets);
}

void DelayNode::update(uint32_t elapsedMillis) {
	for(int i = 0; i < leds.size(); i++){
		uint32_t offset = offsets[i];
		if(elapsedMillis > offset){
			Sequence::apply(elapsedMillis - offset, sequence, *leds.get(i));
		}
	}
}

bool DelayNode::isRepOver(uint32_t elapsedMillis) {
	return sequence.getDuration() + maxOffset > elapsedMillis;
}
