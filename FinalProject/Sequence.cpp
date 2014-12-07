#include "Arduino.h"
#include "Sequence.h"
#include "stdint.h"
/*
 * 	Constructor.  Initializes the pins and the instance variables.
 */
Sequence::Sequence()
{
	// Define pins for the LED display:
	this->frames = Keyframe[20]; //COMPLETE RESIZING / CHANGE INIT SIZE FROM 20 IF YOU WANT
	this->num_frames = 0;    
}

void Sequence::addRGB(uint16_t duration, Color c){
	RGBKeyframe frame;
	frame.duration = duration;
	frame.value = color;
	frames[num_frames]  =  frame;
	num_frames++;
}

void Sequence::addLed(uint16_t duration, int value){
	LedKeyframe frame;
	frame.duration = duration;
	frame.value = value;
	frames[num_frames]  =  frame;
	num_frames++;
}

struct RGBKeyframe {
  uint16_t duration;		// offset in ms
  Color value;
};

struct LedKeyframe {
  uint16_t duration;		// offset in ms
  int value;
};

struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};