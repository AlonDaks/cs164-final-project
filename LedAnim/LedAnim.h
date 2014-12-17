/* LedAnim.h
 * Imports the LedAnim library.
 */

#ifndef LED_ANIM_H
#define LED_ANIM_H

#include "Led.h"
#include "AnimNode.h"
#include "Sequence.h"
#include "AnimPlayer.h"
#include "Array.h"

uint32_t seconds(float secs) {
	return (uint32_t) (secs * 1000 + 0.5);		//rounding conversion
}

uint32_t minSec(uint32_t mins, uint32_t secs) {
	return (60 * mins + secs) * 1000;
}

#endif