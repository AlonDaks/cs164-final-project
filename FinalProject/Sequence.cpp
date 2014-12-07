#include "Sequence.h"

Sequence::Sequence()
{
	// Define pins for the LED display:
	this->max_frames = 20;
	this->frames = (LedKeyframe*) malloc(this->max_frames * sizeof(LedKeyframe));
	this->num_frames = 0;    
}

Sequence::~Sequence()
{
	free(this->frames);
}

// void Sequence::addRGB(uint16_t duration, Color c){
// 	RGBKeyframe frame;
// 	frame.duration = duration;
// 	frame.value = color;
// 	frames[num_frames]  =  frame;
// 	num_frames++;
// }

void Sequence::addLed(uint16_t duration, uint8_t value){
	if (this->num_frames < this->max_frames) {
		this->frames[this->num_frames].duration = duration;
		this->frames[this->num_frames].value = value;
		this->num_frames++;
	}
}
