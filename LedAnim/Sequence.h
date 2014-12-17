#ifndef LED_ANIM_SEQUENCE_H
#define LED_ANIM_SEQUENCE_H

#include "stdint.h"
#include "Color.h"

/* Transition constants */
extern const uint8_t TR_NONE;
extern const uint8_t TR_LERP;

class ILed;

struct Keyframe {
	uint32_t duration;
	Color value;
	uint8_t transition;
};

class Sequence {
public:
	static void update(uint32_t elapsedMillis, const Sequence& seq, /* out */ Color& currentColor);
	static void apply(uint32_t elapsedMillis, const Sequence& seq, ILed& led);

public:
	Sequence();
	~Sequence();

	Sequence& append(const Keyframe& frame);
	Sequence& append(uint32_t duration, const Color& color);
	Sequence& append(uint32_t duration, const Color& color, uint8_t transition);

	Sequence& colorAt(uint32_t offset, const Color& color);
	Sequence& colorAt(uint32_t offset, const Color& color, uint8_t transition);
	Sequence& colorAt(uint32_t offset, uint32_t duration, const Color& color);
	Sequence& colorAt(uint32_t offset, uint32_t duration, const Color& color, uint8_t transition);

	Sequence& insert(uint16_t index, const Keyframe& frame);

	Keyframe get(uint16_t index);
	Keyframe remove(uint16_t index);
	
	uint16_t size() const;
	void print();
	uint32_t getDuration();

private:
	Keyframe* frames;
	uint16_t count;
	uint16_t capacity;
	uint32_t duration;
	void resize(const uint16_t newCapacity);
	void exit(const char* message) const;
};

#endif