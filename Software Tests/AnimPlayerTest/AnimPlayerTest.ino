#include <LedAnim.h>
#include "PushButton.h"

///////////////////////////////////
// Setup Hardware:

const int aPin1 = 22;  // anode
const int rPin1 = 23;  // red pin
const int gPin1 = 21;  // green pin
const int bPin1 = 20;  // blue pin

const int aPin2 = 4;  // anode
const int rPin2 = 3;  // red pin
const int gPin2 = 5;  // green pin
const int bPin2 = 6;  // blue pin

const int brightness = 10;

RgbLedCA rgbLed1 = RgbLedCA(rPin1, gPin1, bPin1, aPin1, true, brightness);
RgbLedCA rgbLed2 = RgbLedCA(rPin2, gPin2, bPin2, aPin2, true, brightness);

const int pushButtonPin = 14;  

///////////////////////////////////
// Define AnimNodes:

struct PlayRed : public TimeNode {
  PlayRed(uint32_t dur) : TimeNode(dur) {}
  void update(uint32_t elapsedMillis) {
    rgbLed1.setColor(RED);
  }
};

struct PlayGreen : public TimeNode {
  PlayGreen(uint32_t dur) : TimeNode(dur) {}
  void update(uint32_t elapsedMillis) {
    rgbLed1.setColor(GREEN);
  }
};

struct PlayBlue : public TimeNode {
  PlayBlue(uint32_t dur) : TimeNode(dur) {}
  void update(uint32_t elapsedMillis) {
    rgbLed1.setColor(BLUE);
  }
};

struct PlayYellow : public TimeNode {
  PlayYellow(uint32_t dur) : TimeNode(dur) {}
  void update(uint32_t elapsedMillis) {
    rgbLed2.setColor(YELLOW);
  }
};

struct PlayCyan : public TimeNode {
  PlayCyan(uint32_t dur) : TimeNode(dur) {}
  void update(uint32_t elapsedMillis) {
    rgbLed2.setColor(CYAN);
  }
};

///////////////////////////////////
// Instantiate:

const uint16_t rgbTime = 1000;
const uint16_t ycTime = 1666;

PlayRed redAnim = PlayRed(rgbTime);
PlayGreen greenAnim = PlayGreen(rgbTime);
PlayBlue blueAnim = PlayBlue(rgbTime);

PlayYellow yellowAnim = PlayYellow(ycTime);
PlayCyan cyanAnim = PlayCyan(ycTime);

AnimPlayer player = AnimPlayer();

///////////////////////////////////

int rgbAnimId;
int ycAnimId;

void setup() {
  redAnim.next(greenAnim).next(blueAnim).next(redAnim);
  yellowAnim.next(cyanAnim).next(yellowAnim);
  
  rgbAnimId = player.play(redAnim);
  ycAnimId = player.play(yellowAnim);
}

int test = 1;

void doTest() {
}

void loop() {
  if (test) {
    delay(2000);
    doTest();
    test = 0;
  }
  
  player.update();
}
