#include <Led.h>
#include <RGBLed.h>
#include <Sequence.h>
#include <SequencePlayer.h>

int ledPin = 13;
SequencePlayer sp = SequencePlayer();
Sequence seq = Sequence();
Led led = Led(ledPin);

void setup() {
  Serial.print("Hi");
  for (int i = 0; i < 20; i++) {
    seq.addLed(3000, (i+1) % 2);
  }
  
  sp.addActiveLight(led, seq);
}

void loop() {
  //seq.print();
  sp.update();
}
