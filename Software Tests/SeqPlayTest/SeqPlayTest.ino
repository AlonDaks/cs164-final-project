#include <LedAnim.h>

int test = 1;

///////////////////////////////////

class DoNothingFunc : public AnimFunc {
  void update(uint16_t elapsedTime) {
    // do nothing 
  }
  uint16_t durationInMillis() { return 10; }
};

///////////////////////////////////

DoNothingFunc f = DoNothingFunc();

SeqAnim sq1 = SeqAnim();
SeqAnim sq2 = SeqAnim();
FnAnim fnA1 = FnAnim(f);
FnAnim fnA2 = FnAnim(f);


void doTest() {
  //Serial.println(fnA2.isEnd());
}

void setup() {
  sq2.setNext(sq2);
}

void loop() {
  delay(2000);
  if (test) {
    doTest();
    test = 0;
  }
}
