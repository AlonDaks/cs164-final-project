#include <Color.h>
#include <Led.h>
#include <LedAnim.h>
#include <AnimPlayer.h>
#include "PushButton.h"

///////////////////////////////////
// Hardware:

const int cPin1 = 22;  // cathode
const int rPin1 = 23;  // red pin
const int gPin1 = 21;  // green pin
const int bPin1 = 20;  // blue pin

const int cPin2 = 4;  // cathode
const int rPin2 = 3;  // red pin
const int gPin2 = 5;  // green pin
const int bPin2 = 6;  // blue pin

const int brightness = 10;

RgbLed rgbLed1 = RgbLed(brightness, cPin1, rPin1, gPin1, bPin1);
RgbLed rgbLed2 = RgbLed(brightness, cPin2, rPin2, gPin2, bPin2);

const int pushButtonPin = 14;  

///////////////////////////////////
// AnimFuncs:

uint16_t rgbTime = 1000;

// Sets the color of the LED to red
struct PlayRed : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed1.setColor(RED);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > rgbTime; }
};

// Sets the color of the LED to green
struct PlayGreen : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed1.setColor(GREEN);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > rgbTime; }
};

// Sets the color of the LED to blue
struct PlayBlue : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed1.setColor(BLUE);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > rgbTime; }
};

///////////////////////////////////
// AnimFunc set 2

uint16_t bcTime = 1666;

// Sets the color of the LED to green
struct PlayYellow : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed2.setColor(YELLOW);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > bcTime; }
};

// Sets the color of the LED to blue
struct PlayCyan : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed2.setColor(CYAN);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > bcTime; }
};

///////////////////////////////////

PlayRed pr;
PlayGreen pg;
PlayBlue pb;

LedAnim redAnim = LedAnim(pr);
LedAnim greenAnim = LedAnim(pg);
LedAnim blueAnim = LedAnim(pb);

PlayYellow py;
PlayCyan pc;

LedAnim yellowAnim = LedAnim(py);
LedAnim cyanAnim = LedAnim(pc);

AnimPlayer player = AnimPlayer();

///////////////////////////////////

int rgbAnimId;
int ycAnimId;

void setup() {
  Serial.println("Setting up animations");
  redAnim.setNext(greenAnim);
  greenAnim.setNext(blueAnim);
  blueAnim.setNext(redAnim);
  
  yellowAnim.setNext(cyanAnim);
  cyanAnim.setNext(yellowAnim);
  Serial.println("Finished setting up animations");
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
