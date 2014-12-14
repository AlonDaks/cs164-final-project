#include <AnimPlayer.h>
#include <Led.h>
#include <LedAnim.h>
#include <Sequence.h>

///////////////////////////////////

int cPin = 22;  // cathode
int rPin = 23;  // red pin
int gPin = 21;  // green pin
int bPin = 20;  // blue pin
int brightness = 10;

///////////////////////////////////

RgbLed rgbLed = RgbLed(brightness, cPin, rPin, gPin, bPin);
Color currentColor;

// Create Sequence 
Sequence seq = Sequence();

// Subclass AnimFunc with custom update
struct LERPTest : public AnimFunc {
  void update(uint16_t elapsedTime) {
    Sequence::applySequence(elapsedTime, seq, rgbLed);
  }
  bool isOver(uint16_t elapsedTime) {
    return elapsedTime > seq.getDuration() * 10; // Loops over the sequence twice
  }
};

LERPTest lt; // Create AnimFunc
LedAnim anim = LedAnim(lt); // Create anim

AnimPlayer player = AnimPlayer();

void setup() {
  Keyframe kf1 = {1000, OCEAN, 1 }; // LERP transition
  Keyframe kf2 = {500, RASPBERRY, 1 }; // NONE transition
  seq.append(kf1).append(kf2);
  
  uint16_t rec1 = player.play(anim);
}

void loop() {
  player.update();
}
