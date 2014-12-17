#include "Color.h"

const Color RED = {255, 0, 0};
const Color ORANGE = {255, 127, 0};
const Color YELLOW = {255, 255, 0};
const Color SPRING_GREEN = {127, 255, 0};
const Color GREEN = {0, 255, 0};
const Color TURQUOISE = {0, 255, 127};
const Color CYAN = {0, 255, 255};
const Color OCEAN = {0, 127, 255};
const Color BLUE = {0, 0, 255};
const Color VIOLET = {127, 0, 255};
const Color MAGENTA = {255, 0, 255};
const Color RASPBERRY = {255, 0, 127};
const Color WHITE = {255, 255, 255};
const Color OFF = {0, 0, 0};

Color::Color() {}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
: red(red), green(green), blue(blue) { }

Color::Color(uint32_t hex) {
	red = (uint8_t) (hex & 0xFF);
	green = (uint8_t) ((hex >> 8) & 0xFF);
	blue = (uint8_t) ((hex >> 16) & 0xFF);
}

uint32_t Color::toInt() const {
	uint32_t c = red;
	c <<= 8;
	c |= green;
	c <<= 8;
	c |= blue;
	return c;
}

uint32_t Color::toInt(const uint8_t brightness) const {
	uint32_t c;
	c = (((uint16_t) red * brightness) / 255) & 0xFF;
	c <<= 8;
	c |= (((uint16_t) green * brightness) / 255) & 0xFF;
	c <<= 8;
	c |= (((uint16_t) blue * brightness) / 255) & 0xFF;
	return c;
}