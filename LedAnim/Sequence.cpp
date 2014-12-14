#include "Sequence.h"
#include "Led.h"
#include <Arduino.h>

#define DEFAULT_SIZE 8
#define MIN_SIZE 4

uint8_t TR_NONE = 0;
uint8_t TR_LERP = 1;

Keyframe invalid;

Sequence::Sequence() {
	frames = (Keyframe *) malloc(sizeof(Keyframe) * DEFAULT_SIZE);
	if (!frames) {
		//exit("Allocation failed");
	}
	count = 0;
	capacity = DEFAULT_SIZE;
	duration = 0;
}

Sequence::~Sequence() {
	free(frames);
}

void Sequence::update(uint32_t elapsedMillis, Sequence& seq, /* out */ Color& currentColor) {
	uint32_t timeRemaining = elapsedMillis % seq.duration;
	for (int i = 0; i < seq.count; i++) { // Find correct frame
		Keyframe curFrame = seq.frames[i];
		if (timeRemaining < curFrame.duration) {
			if (curFrame.transition == TR_LERP) {
				Keyframe nextFrame = seq.frames[ (i+1) % seq.count ];
				float interp = (float) timeRemaining / (float) curFrame.duration;
				currentColor.red = (1-interp) * curFrame.value.red + interp * nextFrame.value.red;
				currentColor.green = (1-interp) * curFrame.value.green + interp * nextFrame.value.green;
				currentColor.blue = (1-interp) * curFrame.value.blue + interp * nextFrame.value.blue;
				/*Serial.print("R: ");
				Serial.print(currentColor.red);
				Serial.print(" G: ");
				Serial.print(currentColor.green);
				Serial.print(" B: ");
				Serial.println(currentColor.blue);*/
			} else {
				currentColor = curFrame.value;
			}
			break;
		}
		timeRemaining -= curFrame.duration;
	}
}

void Sequence::apply(uint32_t elapsedMillis, Sequence& seq, ILed& led) {
	Color c;
	update(elapsedMillis, seq, c);
	led.setColor(c);
}

Sequence& Sequence::append(const Keyframe frame) {
	if (count == capacity) {
		resize(2 * capacity);
	}
	frames[count] = frame;
	count++;
	duration += frame.duration;
	return *this;
}

Sequence& Sequence::insert(uint16_t index, const Keyframe frame) {
	if (index <= count) {
		if (count == capacity) {
			resize(2 * capacity);
		}
		uint16_t numAfter = count - index;
		if (numAfter > 0) {
			memmove(frames + index + 1, frames + index, sizeof(Keyframe) * numAfter);
		}
		frames[index] = frame;
		count++;
		duration += frame.duration;
	}
	return *this;
}

Keyframe Sequence::get(uint16_t index) {
	if (index < count) {
        return frames[index];
    } else {
        return invalid;
    }
}

Keyframe Sequence::remove(uint16_t index) {
    if (index < count) {
        Keyframe frame = frames[index];
        uint16_t numAfter = count - index - 1;
        if (numAfter > 0) {
            memmove(frames + index, frames + index + 1, sizeof(Keyframe) * numAfter); 
        }
        count--;
        duration -= frame.duration;
        return frame;
    } else {
        return invalid;
    }
}

uint16_t Sequence::size() const {
    return count;
}

void Sequence::resize(const uint16_t newCapacity) {
	frames = (Keyframe* ) realloc(frames, sizeof(Keyframe) * newCapacity);
	if (!frames) {
		exit("Allocation failed");
	}
	capacity = newCapacity;
}

void Sequence::exit(const char* message) const {
    Serial.print("Error: ");
    Serial.print(message);
    Serial.print("\n");
}

void Sequence::print(uint32_t elapsedMillis) {
	uint32_t timeRemaining = elapsedMillis % duration;
	for (int i = 0; i < count; i++) { // Find correct frame
		Keyframe frame = frames[i];
		if (timeRemaining < frame.duration) {
			Serial.print(frame.value.red);
			Serial.print("\n");
			Serial.print(frame.value.green);
			Serial.print("\n");
			Serial.print(frame.value.blue);
			Serial.print("\n");
			break;
		}
		timeRemaining -= frame.duration;
	}
}

uint32_t Sequence::getDuration() {
	return duration;
}

#undef DEFAULT_SIZE
#undef MIN_SIZE
