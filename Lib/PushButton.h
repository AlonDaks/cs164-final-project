/* A simple pushbutton that filters out repeated clicks. */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H 

#include "Arduino.h"

class PushButton {
public:
	PushButton(unsigned int pin);
	void update();
	bool isPressed();
private:
	unsigned long lastPressMs;
	unsigned long pressDelayMs;
	bool isPressed;
	unsigned int pin;
};

PushButton::PushButton(unsigned int pin, unsigned long delay)
	: lastPressMs(0), pressDelayMs(delay), isPressed(false), pin(pin)
{
	pinMode(pin, INPUT);
}

void PushButton::update() {
	isPressed = false;

	if (digitalRead(buttonPin) == HIGH) {
		unsigned long currentMs = millis();
		if (currentMs - lastPressMs > pressDelayMs) {
			isPressed = true;
			lastPressMs = currentMs;
		}
	}
}

bool PushButton::isPressed() {
	return isPressed;
}

#endif 