#include "Sequence.h"
#include <stdlib.h>
#include <Arduino.h>

#define DEFAULT_SIZE 8
#define MIN_SIZE 4

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

void Sequence::updateSequence(uint16_t elapsedTime, Sequence& seq, /* out */ Color& currentColor) {
	uint16_t timeRemaining = elapsedTime % seq.duration;
	for (int i = 0; i < seq.count; i++) { // Find correct frame
		Keyframe frame = seq.frames[i];
		if (timeRemaining < frame.duration) {
			currentColor.red = frame.value.red;
			currentColor.green = frame.value.green;
			currentColor.blue = frame.value.blue;
			break;
		}
		timeRemaining -= frame.duration;
	}
}

void Sequence::append(const Keyframe frame) {
	if (count == capacity) {
		resize(2 * capacity);
	}
	frames[count] = frame;
	count++;
	duration += frame.duration;
}

void Sequence::insert(uint16_t index, const Keyframe frame) {
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
}

Keyframe Sequence::get(uint16_t index) {
	if (index < count) {
        return frames[index];
    } else {
        //return nullptr;
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
        //return nullptr;
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

#undef DEFAULT_SIZE
#undef MIN_SIZE
