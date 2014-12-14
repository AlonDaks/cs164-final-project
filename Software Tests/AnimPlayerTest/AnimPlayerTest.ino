#include <Led.h>
#include <LedAnim.h>
#include <AnimPlayer.h>

///////////////////////////////////
// Hardware:
const int cPin = 22;  // cathode
const int rPin = 23;  // red pin
const int gPin = 21;  // green pin
const int bPin = 20;  // blue pin
const int brightness = 10;

RgbLed rgbLed = RgbLed(brightness, cPin, rPin, gPin, bPin);

const int pushButtonPin = 14;  

///////////////////////////////////
// AnimFuncs:

uint16_t rgbTime = 1000;

// Sets the color of the LED to red
struct PlayRed : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed.setColor(255, 0, 0);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > rgbTime; }
};

// Sets the color of the LED to green
struct PlayGreen : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed.setColor(0, 255, 0);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > rgbTime; }
};

// Sets the color of the LED to blue
struct PlayBlue : public AnimFunc {
  void update(uint16_t elapsedTime) {
    rgbLed.setColor(0, 0, 255);
  }
  bool isOver(uint16_t elapsedTime) { return elapsedTime > rgbTime; }
};

///////////////////////////////////

PlayRed pr;
PlayGreen pg;
PlayBlue pb;

LedAnim redAnim = LedAnim(pr);
LedAnim greenAnim = LedAnim(pg);
LedAnim blueAnim = LedAnim(pb);
AnimPlayer player = AnimPlayer();

///////////////////////////////////

int rgbAnimId;

void setup() {
  Serial.println("Setting up animations");
  redAnim.setNext(greenAnim);
  greenAnim.setNext(blueAnim);
  blueAnim.setNext(redAnim);
  Serial.println("Finished setting up animations");
  rgbAnimId = player.play(redAnim);
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
