/* Basic test with RGB led */
#include <Led.h>

int cPin = 22;  // cathode
int rPin = 23;  // red pin
int gPin = 21;  // green pin
int bPin = 20;  // blue pin
int brightness = 255;

RgbLed rgbLed = RgbLed(brightness, cPin, rPin, gPin, bPin);

/*void setColor(unsigned int color) {
  analogWrite(cPin, maxVoltage);
  analogWrite(bPin, maxVoltage - ((color & 0xFF) * maxVoltage)/0xFF);
  color = color >> 8;
  analogWrite(gPin, maxVoltage - ((color & 0xFF) * maxVoltage)/0xFF);
  color = color >> 8;
  analogWrite(rPin, maxVoltage - ((color & 0xFF) * maxVoltage)/0xFF);
}*/

void setup() {
  /*pinMode(cPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);*/
}

void loop() {
  rgbLed.setColor(0xFF, 0x00, 0xCC);
  delay(1000);
  rgbLed.setColor(0x00, 0xFF, 0x00);
  delay(1000);
}
