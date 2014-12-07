#ifndef RGBLED_H
#define RGBLED_H


#include "Arduino.h"
#include "Sequence.h"
#include "stdint.h"

class RGBLed
{
  public:
    RGBLed(int red_pin, int green_pin, int blue_pin);
    void setValue(Color c);
  private:
    int red_pin;
    int green_pin;
    int blue_pin;
};

#endif