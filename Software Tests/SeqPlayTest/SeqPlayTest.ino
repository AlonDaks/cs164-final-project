#include <LedAnim.h>
#include <AnimPlayer.h>
int test = 1;

///////////////////////////////////
// AnimFuncs:

/* Plays green colors */
struct GreenFunc : public AnimFunc {
  void update(uint16_t elapsedTime) {
    // do nothing 
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > 1000; }
};

///////////////////////////////////

DoNothingFunc f;
LedAnim a1 = LedAnim(f);
LedAnim a2 = LedAnim(f);

Color c;
Sequence seq = Sequence();

void doTest() {
  //Serial.println(fnA2.isEnd());
  Sequence::updateSequence(0, seq, c);
}

void setup() {
  a1.setNext(a2);
  a2.setNext(a2);
}

void loop() {
  delay(2000);
  if (test) {
    doTest();
    test = 0;
  }
}
