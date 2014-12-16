#include <LedAnim.h>
#include <Adafruit_WS2801.h>
#include <SPI.h>
#include "LedStrip.h"

///////////////////////////////////

const int dataPin = 15;    //yellow
const int clockPin = 16;   //green
LedStrip ledStrip = LedStrip(25, dataPin, clockPin, 10);
AnimPlayer player = AnimPlayer();

///////////////////////////////////

unsigned int delayFunc(int index) {
  return 100*index;
}
Sequence seq = Sequence();
SeqNode anim = SeqNode(ledStrip, seq, FOREVER); // Create anim
//DelayNode anim = DelayNode(ledStrip.getLights(), seq, delayFunc, FOREVER);

void setup() {
  seq.append(seconds(1), RED, TR_LERP)
     .append(seconds(1), GREEN, TR_LERP)
     .append(seconds(1), BLUE, TR_LERP);
  /*
  // colorAt() tests
  seq.append(RED, TR_NONE, 2000);
  seq.colorAt(1000, GREEN, TR_NONE, 1000);
  seq.append(RED, TR_NONE, 1000);
  seq.colorAt(2000, BLUE, TR_NONE, 500);
  seq.colorAt(3000, WHITE, TR_NONE, 1000);
  */
  uint16_t rec1 = player.play(anim);
}

int test = 1;

void doTest() {
  seq.print();
 // Serial.println(anim.totalDuration());
}

void loop() {
  if (test) {
    delay(2000);
    doTest();
    test = 0;
  }
  
  player.update();
}
