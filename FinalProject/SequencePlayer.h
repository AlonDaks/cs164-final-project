#ifndef SEQUENCEPLAYER_H
#define SEQUENCEPLAYER_H

#include "Arduino.h"
#include "stdint.h"
#include "Led.h"
#include "Sequence.h"

struct ActiveLight {
  Led* led;
  Sequence* seq;
  uint curIndex;  // index of last processed keyframe
  uint elapsedTime;
};

class SequencePlayer
{
  public:
  	SequencePlayer();
    void start();
    void update();
    void stop();
    void addActiveLight(Led& led, Sequence& seq);
  private:
    ActiveLight active_lights[20];
    uint8_t num_active_lights;
    unsigned long last_update_time;
};

#endif