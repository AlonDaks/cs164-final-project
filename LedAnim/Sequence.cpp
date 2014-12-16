#include "Sequence.h"
#include "Led.h"
#include "Utils.h"

#define DEFAULT_SIZE 8
#define MIN_SIZE 4

const uint8_t TR_NONE = 0;
const uint8_t TR_LERP = 1;

Keyframe invalid;

Sequence::Sequence() : count(0), capacity(DEFAULT_SIZE), duration(0) {
	frames = (Keyframe *) malloc(sizeof(Keyframe) * DEFAULT_SIZE);
	if (!frames) {
		Log::error("Allocation failed");
	}
}

Sequence::~Sequence() {
	free(frames);
}

void Sequence::update(uint32_t elapsedMillis, const Sequence& seq, /* out */ Color& currentColor) {
	uint32_t timeRemaining = elapsedMillis % seq.duration;
	for (int i = 0; i < seq.count; i++) { // Find correct frame
		Keyframe& curFrame = seq.frames[i];
		if (timeRemaining <= curFrame.duration) {
			if (curFrame.transition == TR_LERP) {
				Keyframe& nextFrame = seq.frames[ (i+1) % seq.count ];
				float interp = (float) timeRemaining / (float) curFrame.duration;
				currentColor.red = (1-interp) * curFrame.value.red + interp * nextFrame.value.red;
				currentColor.green = (1-interp) * curFrame.value.green + interp * nextFrame.value.green;
				currentColor.blue = (1-interp) * curFrame.value.blue + interp * nextFrame.value.blue;
				/*if (timeRemaining == 2000) {
					Serial.print("Time = 2000ms"); Serial.print(" {R: ");
					Serial.print(currentColor.red); Serial.print(" G: ");
					Serial.print(currentColor.green); Serial.print(" B: ");
					Serial.print(currentColor.blue); Serial.println("} ");
				}*/
			} else {
				currentColor = curFrame.value;
			}
			break;
		}
		timeRemaining -= curFrame.duration;
	}
}

void Sequence::apply(uint32_t elapsedMillis, const Sequence& seq, ILed& led) {
	Color c;
	update(elapsedMillis, seq, c);
	led.setColor(c);
}

Sequence& Sequence::append(const Keyframe& frame) {
	if (count == capacity) {
		resize(2 * capacity);
	}
	frames[count] = frame;
	count++;
	duration += frame.duration;
	return *this;
}

Sequence& Sequence::append(uint32_t duration, const Color& color) {
	Keyframe frame = {duration, color, TR_NONE};
	return append(frame);
}

Sequence& Sequence::append(uint32_t duration, const Color& color, uint8_t transition) {
	Keyframe frame = {duration, color, transition};
	return append(frame);
}

Sequence& Sequence::colorAt(uint32_t offset, const Color& color) {
	return colorAt(offset, 0, color, TR_NONE);
}

Sequence& Sequence::colorAt(uint32_t offset, const Color& color, uint8_t transition) {
	return colorAt(offset, 0, color, transition);
}

Sequence& Sequence::colorAt(uint32_t offset, uint32_t duration, const Color& color) {
	return colorAt(offset, duration, color, TR_NONE);
}

Sequence& Sequence::colorAt(uint32_t offset, uint32_t duration, const Color& color, uint8_t transition) {
	Keyframe frame = {duration, color, transition};
	for (int i = 0; i < count; i++) {
		Keyframe& curFrame = frames[i];
		if (offset == 0) {
			// if new frame coincides with existing, replace the old frame
			this->duration += (duration - curFrame.duration);				
			curFrame = frame;
			return *this;
		} else if (offset < curFrame.duration) {	
			// if new frame in the middle of existing, truncate old frame and insert (shifting back any later frames)
			this->duration += (offset - curFrame.duration);
			curFrame.duration = offset;
			return insert(i + 1, frame);
		}
		offset -= curFrame.duration;
	}
	// otherwise, append at end (stretch out the last frame to prevent gaps)
	frames[count - 1].duration += offset;
	this->duration += offset;
	return append(frame);
}

Sequence& Sequence::insert(uint16_t index, const Keyframe& frame) {
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

uint32_t Sequence::getDuration() {
	return duration;
}

void Sequence::resize(const uint16_t newCapacity) {
	frames = (Keyframe* ) realloc(frames, sizeof(Keyframe) * newCapacity);
	if (!frames) {
		Log::error("Allocation failed");
	}
	capacity = newCapacity;
}

void Sequence::print() {
	for (int i = 0; i < count; i++) {
		Keyframe frame = frames[i];
		Serial.print("Duration: ");
		Serial.print(frame.duration);
		Serial.print("{ R: ");
		Serial.print(frame.value.red);
		Serial.print(" G: ");
		Serial.print(frame.value.green);
		Serial.print(" B: ");
		Serial.print(frame.value.blue);
		Serial.print(" }\n");
	}
}

#undef DEFAULT_SIZE
#undef MIN_SIZE
