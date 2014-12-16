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

Sequence seq = Sequence();
SeqNode anim = SeqNode(ledStrip, seq, FOREVER); // Create anim

void setup() {
  seq.append(seconds(1), OCEAN, TR_LERP)
     .append(seconds(1), YELLOW, TR_LERP)
     .append(seconds(1), Color(3, 125, 223), TR_LERP)
     .append(seconds(1), MAGENTA, TR_LERP);
  /*
  // colorAt() tests
  seq.append(RED, TR_NONE, 2000);
  seq.colorAt(1000, GREEN, TR_NONE, 1000);
  seq.append(RED, TR_NONE, 1000);
  seq.colorAt(2000, BLUE, TR_NONE, 500);
  seq.colorAt(3000, WHITE, TR_NONE, 1000);
  */
  ledStrip.begin();
  uint16_t rec1 = player.play(anim);
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
