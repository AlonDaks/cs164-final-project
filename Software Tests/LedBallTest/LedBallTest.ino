#include <LedAnim.h>
#include <Adafruit_WS2801.h>
#include <SPI.h>
#include "LedStrip.h"
#include "LedBall.h"

///////////////////////////////////

const int dataPin = 15;    //yellow
const int clockPin = 16;   //green
LedStrip ledStrip = LedStrip(25, dataPin, clockPin, 10);
AnimPlayer player = AnimPlayer();

///////////////////////////////////

struct SpiralNode : public TimeNode {
  uint32_t delay;
  void update(uint32_t elapsedMillis) {
    for (int i = 0; i < ledStrip.size(); ++i) {
      if (elapsedMillis > i * delay) {
        ledStrip.setColor(i, RED);
      } else {
        ledStrip.setColor(i, GREEN);
      }
    }
  }
  SpiralNode(uint32_t delay, Color c) : TimeNode(0), delay(delay) {
    duration = 25 * delay;
  }
};

struct RotateNode : public TimeNode {
  uint32_t msPerDeg;
  void update(uint32_t elapsedMillis) {
    for (int i = 0; i < ledStrip.size(); ++i) {
      if (elapsedMillis / msPerDeg > CIRCLE[i]) {
        ledStrip.setColor(i, BLUE);
      } else {
        ledStrip.setColor(i, RED);
      }
    }
  }
  RotateNode(uint32_t msPerDeg, Color c) : TimeNode(0), msPerDeg(msPerDeg) {
    duration = msPerDeg * 360;
  }
};

struct LevelNode : public TimeNode {
  uint32_t delay;
  void update(uint32_t elapsedMillis) {
    for (int i = 0; i < ledStrip.size(); ++i) {
      if (elapsedMillis > LEVEL[i] * delay) {
        ledStrip.setColor(i, GREEN);
      } else {
        ledStrip.setColor(i, BLUE);
      }
    }
  }
  LevelNode(uint32_t delay, Color c) : TimeNode(0), delay(delay) {
    duration = delay * 3;
  }
};

///////////////////////////////////

Sequence seq = Sequence();
SeqNode anim = SeqNode(ledStrip, seq, 1); // Create anim

SpiralNode spiralRed = SpiralNode(100, RED);
RotateNode rotateBlue = RotateNode(5, BLUE);
LevelNode levelGreen = LevelNode(1000, GREEN);

void setup() {
  // Add keyframes:
  Keyframe kf1 = {1000, OCEAN, TR_LERP }; // LERP transition
  Keyframe kf2 = {1000, YELLOW, TR_LERP }; // NONE transition
  seq.append(kf1).append(kf2);
  
  // Link nodes:
  spiralRed.next(rotateBlue).next(levelGreen).next(spiralRed);
  
  uint16_t rec1 = player.play(spiralRed);
}

void loop() {
  player.update();
}
