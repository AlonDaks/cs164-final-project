/*#include "Sequence.h"
#include <stdlib.h>

Sequence::Sequence() {
	max_frames = 20;
	frames = (LedKeyframe*) malloc(max_frames * sizeof(LedKeyframe));
	num_frames = 0;    
}

Sequence::~Sequence() {
	free(frames);
}

void Sequence::addLed(uint16_t duration, uint8_t value) {
	if (num_frames < max_frames) {
		frames[num_frames].duration = duration;
		frames[num_frames].value = value;
		num_frames++;
	}
}
*/