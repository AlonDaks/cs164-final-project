#include <LedAnim.h>

///////////////////////////////////

// Hardware setup:

int aPin = 22;  // cathode
int rPin = 23;  // red pin
int gPin = 21;  // green pin
int bPin = 20;  // blue pin
int brightness = 255;
RgbLedCA rgbLed = RgbLedCA(rPin, gPin, bPin, aPin, true, brightness);

///////////////////////////////////

AnimPlayer player = AnimPlayer();

Sequence seq = Sequence();
SeqNode anim = SeqNode(rgbLed, seq, 2);

void setup() {
  seq.append(seconds(0.5), OCEAN, TR_LERP)
     .append(seconds(0.5), RASPBERRY, TR_LERP)
     .append(seconds(0.5), GREEN, TR_LERP)
     .append(seconds(0.5), WHITE, TR_LERP);
  player.play(anim);
}

void loop() {
  player.update();
}
