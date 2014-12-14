#include <AnimFunc.h>
#include <AnimPlayer.h>
#include <Array.h>
#include <Colors.h>
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
    Sequence::updateSequence(elapsedTime, seq, currentColor);
    rgbLed.setColor(currentColor.red, currentColor.green, currentColor.blue);
  }
  bool isOver(uint16_t elapsedTime) {
    return elapsedTime > 10000000;
  }
};

LERPTest lt; // Create AnimFunc
LedAnim anim = LedAnim(lt); // Create anim

AnimPlayer player = AnimPlayer();

void setup() {
  Color kfc1 = RED;
  Keyframe kf1 = {1000, kfc1, 0 }; // LERP transition
  Color kfc2 = BLUE;
  Keyframe kf2 = {500, kfc2, 0 }; // NONE transition
  seq.append(kf1);
  seq.append(kf2);
  
  uint16_t rec1 = player.play(anim);
}

void loop() {
  player.update();
}
