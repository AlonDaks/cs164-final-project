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

const int brightness = 100;

RgbLedCA led1 = RgbLedCA(rPin1, gPin1, bPin1, aPin1, true, brightness);
RgbLedCA led2 = RgbLedCA(rPin2, gPin2, bPin2, aPin2, true, brightness);

const int pushButtonPin = 14;
PushButton btn = PushButton(pushButtonPin, 1000);

///////////////////////////////////
// Define Animations:

AnimPlayer player = AnimPlayer();

Sequence rgbSeq = Sequence();
Sequence ycSeq = Sequence();

SeqNode rgbNode;
SeqNode ycNode;

///////////////////////////////////

int rgbAnimId;
int ycAnimId;
int pushCount = 0;

void setup() {
  rgbAnim.append(seconds(0.5), RED).append(seconds(0.5), GREEN).append(seconds(0.5), BLUE);
  ycAnim.append(seconds(0.333), YELLOW).append(seconds(0.333), CYAN);
  
  rgbAnim = SeqNode(led1, rgbSeq, FOREVER);
  ycAnim = SeqNode(led2, ycSeq, FOREVER);
  
  rgbAnimId = player.play(rgbAnim);
  ycAnimId = player.play(ycAnim);
}

void loop() {
  btn.update();
  if (btn.isPressed()) {
    updateLedState();
  }  
  player.update();
}

void updateLedState() {
  switch (pushCount) {
    case 0: {
      player.pause(rgbAnimId);
      break;
    }
    case 1: {
      player.resume(rgbAnimId);
      player.pause(ycAnimId);
      break;
    }
    case 2: {
      player.pause(rgbAnimId);
      break;
    }
    case 3: {
      player.resume(rgbAnimId);
      player.resume(ycAnimId);
      break;
    }
  }
  pushCount = (pushCount+1) % 4;
}
