#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Arduino.h"
#include "stdint.h"


struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct RGBKeyframe {
  uint16_t duration;		// offset in ms
  Color value;
};

struct LedKeyframe {
  uint16_t duration;		// offset in ms
  uint8_t value;
};

class Sequence
{
  public:
    Sequence();
    ~Sequence();
    //void addRGB(uint16_t duration, Color c);
    void addLed(uint16_t duration, uint8_t value);
    LedKeyframe* frames;
    uint16_t num_frames;
    uint16_t max_frames;
};

#endif