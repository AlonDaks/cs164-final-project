#include <LedAnim.h>

///////////////////////////////////

int aPin = 22;  // cathode
int rPin = 23;  // red pin
int gPin = 21;  // green pin
int bPin = 20;  // blue pin
int brightness = 10;
RgbLedCA rgbLed = RgbLedCA(rPin, gPin, bPin, aPin, true, brightness);

///////////////////////////////////

Sequence seq = Sequence();
SeqNode anim = SeqNode(rgbLed, seq, 3); // Create anim

AnimPlayer player = AnimPlayer();

void setup() {
  Keyframe kf1 = {2000, OCEAN, TR_LERP};
  Keyframe kf2 = {1000, RASPBERRY, TR_LERP};
  seq.append(kf1).append(kf2);
  
  uint16_t rec1 = player.play(anim);
}

void loop() {
  player.update();
}
