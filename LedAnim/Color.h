#ifndef LED_ANIM_COLORS_H
#define LED_ANIM_COLORS_H

#include <stdint.h>

struct Color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue);
	Color(uint32_t hex);

	uint32_t toInt() const;
	uint32_t toInt(const uint8_t brightness) const;
};

extern const Color RED;
extern const Color ORANGE;
extern const Color YELLOW;
extern const Color SPRING_GREEN;
extern const Color GREEN;
extern const Color TURQUOISE;
extern const Color CYAN;
extern const Color OCEAN;
extern const Color BLUE;
extern const Color VIOLET;
extern const Color MAGENTA;
extern const Color RASPBERRY;
extern const Color WHITE;
extern const Color OFF;

#endif
