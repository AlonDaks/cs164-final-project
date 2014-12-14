/* A simple pushbutton that filters out repeated clicks. */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "Arduino.h"

class PushButton {
public:
	PushButton(unsigned int pin, unsigned long delay);
	void update();
	bool isPressed();
private:
	unsigned long lastPressMs;
	unsigned long pressDelayMs;
	bool bIsPressed;
	unsigned int pin;
};

PushButton::PushButton(unsigned int pin, unsigned long delay)
	: lastPressMs(0), pressDelayMs(delay), bIsPressed(false), pin(pin)
{
	pinMode(pin, INPUT);
}

void PushButton::update() {
	if (digitalRead(pin) == HIGH) {
		unsigned long currentMs = millis();
		if (currentMs - lastPressMs > pressDelayMs) {
			bIsPressed = true;
			lastPressMs = currentMs;
		}
	}
}

bool PushButton::isPressed() {
	if (bIsPressed) {
		bIsPressed = false;
		return true;
	} else {
		return false;
	}
}

#endif
