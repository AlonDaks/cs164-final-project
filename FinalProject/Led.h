#ifndef LED_H
#define LED_H

#include "Arduino.h"
#include "stdint.h"

class Led
{
  public:
    Led(int pin);
    void setValue(uint8_t value);
  private:
    int pin;
};

#endif