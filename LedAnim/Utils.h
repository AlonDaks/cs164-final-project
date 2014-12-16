#ifndef LED_ANIM_UTILS_H
#define LED_ANIM_UTILS_H

#include "Arduino.h"

class Log {
public:
	static void error(const char* message) {
		Serial.print("Error: ");
    	Serial.print(message);
    	Serial.print("\n");
	}
};


#endif
