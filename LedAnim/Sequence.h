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

	Sequence& append(const Keyframe frame);
	Sequence& insert(uint16_t index, const Keyframe frame);
	Keyframe get(uint16_t index);
	Keyframe remove(uint16_t index);
	uint16_t size() const;
	void print(uint16_t elapsedTime);
	uint16_t getDuration();

private:
	Keyframe* frames;
	uint16_t count;
	uint16_t capacity;
	uint16_t duration;

	void resize(const uint16_t newCapacity);
	void exit(const char* message) const;
};

#endif