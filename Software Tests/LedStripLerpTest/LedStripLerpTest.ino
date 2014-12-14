
#include <AnimPlayer.h>
#include <Led.h>
#include <LedAnim.h>
#include <Sequence.h>
#include <Adafruit_WS2801.h>
#include <SPI.h>
#include "LedStrip.h"

///////////////////////////////////

const int dataPin = 16;    //yellow
const int clockPin = 15;   //green
LedStrip ledStrip = LedStrip(25, dataPin, clockPin);

///////////////////////////////////

Color currentColor;

// Create Sequence 
Sequence seq = Sequence();

// Subclass AnimFunc with custom update
struct LERPTest : public AnimFunc {
  void update(uint16_t elapsedTime) {
    Sequence::applySequence(elapsedTime, seq, ledStrip);
  }
  bool isOver(uint16_t elapsedTime) {
    return elapsedTime > 10000000;
  }
};

LERPTest lt; // Create AnimFunc
LedAnim anim = LedAnim(lt); // Create anim

AnimPlayer player = AnimPlayer();

void setup() {
  Keyframe kf1 = {1000, OCEAN, 1 }; // LERP transition
  Keyframe kf2 = {1000, YELLOW, 1 }; // NONE transition
  seq.append(kf1).append(kf2);
  
  ledStrip.begin();
  uint16_t rec1 = player.play(anim);
}

void loop() {
  player.update();
}
