#ifndef SEQUENCEPLAYER_H
#define SEQUENCEPLAYER_H

#include "Arduino.h"
#include "stdint.h"

class SequencePlayer
{
  public:
    void start();
    void update();
    void stop();
  private:
    ActiveLight[] activeLights;
};

#endif