#ifndef LED_ANIM_COLOR_H
#define LED_ANIM_COLOR_H

#include <stdint.h>

struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

Color RED = {255, 0, 0};
Color ORANGE = {255, 125, 0};
Color YELLOW = {255, 255, 0};
Color SPRING_GREEN = {125, 255, 0};
Color GREEN = {0, 255, 0};
Color TURQUOISE = {0, 255, 125};
Color CYAN = {0, 255, 255};
Color OCEAN = {0, 125, 255};
Color BLUE = {0, 0, 255};
Color VIOLET = {125, 0, 255};
Color MAGENTA = {255, 0, 255};
Color RASPBERRY = {255, 0, 125};

#endif
