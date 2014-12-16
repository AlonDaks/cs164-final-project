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
  seq.append(2000, OCEAN, TR_LERP)
     .append(2000, RASPBERRY, TR_LERP);
  
  player.play(anim);
}

int test = 1;

void doTest() {
  seq.print();
}

void loop() {
  if (test) {
    delay(2000);
    doTest();
    test = 0;
  }
  
  player.update();
}
