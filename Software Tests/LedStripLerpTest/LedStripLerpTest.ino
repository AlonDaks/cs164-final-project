#include <LedAnim.h>
#include <Adafruit_WS2801.h>
#include <SPI.h>
#include "LedStrip.h"

///////////////////////////////////

const int dataPin = 15;    //yellow
const int clockPin = 16;   //green
LedStrip ledStrip = LedStrip(25, dataPin, clockPin, 10);

///////////////////////////////////

Sequence seq = Sequence();
SeqNode anim = SeqNode(ledStrip, seq, FOREVER); // Create anim
AnimPlayer player = AnimPlayer();

void setup() {
  Keyframe kf1 = {1000, OCEAN, true };
  Keyframe kf2 = {1000, YELLOW, true };
  Keyframe kf3 = {1000, RED, true }; 
  Keyframe kf4 = {1000, MAGENTA, true };
  seq.append(kf1).append(kf2).append(kf3).append(kf4);
  
  ledStrip.begin();
  uint16_t rec1 = player.play(anim);
}

void loop() {
  player.update();
}
