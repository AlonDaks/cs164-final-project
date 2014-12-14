#include <Led.h>
#include <Sequence.h>

///////////////////////////////////

int cPin = 22;  // cathode
int rPin = 23;  // red pin
int gPin = 21;  // green pin
int bPin = 20;  // blue pin
int brightness = 20;

RgbLed rgbLed = RgbLed(brightness, cPin, rPin, gPin, bPin);

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  analogWrite(cPin, brightness);
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}

Color c;
Sequence seq = Sequence();

void setup() {
  Color kfc1 = { 255,0,0 };
  Keyframe kf1 = {
    100, //duration
    kfc1, // color
    0 // NONE transition
  };
  Color kfc2 = { 0,255,0 };
  Keyframe kf2 = {
    100, //duration
    kfc2, // color
    1 // LERP transition
  };
  seq.append(kf1);
  seq.append(kf2);
  
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop() {
  delay(2000);
  Sequence::updateSequence(25, seq, c);
  rgbLed.setColor(c.red, c.green, c.blue);
  delay(2000);
  Sequence::updateSequence(150, seq, c);
  rgbLed.setColor(c.red, c.green, c.blue);
  delay(2000);
  Sequence::updateSequence(220, seq, c);
  rgbLed.setColor(c.red, c.green, c.blue);
}
