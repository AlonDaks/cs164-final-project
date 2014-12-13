#ifndef LED_ANIM_SEQUENCE_H
#define LED_ANIM_SEQUENCE_H

#include "stdint.h"

struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct Keyframe {
	uint16_t duration;
	Color value;
	uint8_t transition;
};

class Sequence {
public:
	static void updateSequence(uint16_t elapsedTime, Sequence& seq, /* out */ Color& currentColor);
public:
	Sequence();
	~Sequence();
private:
	Keyframe* frames;
	uint16_t num_frames;
	uint16_t max_frames;
};

#endif