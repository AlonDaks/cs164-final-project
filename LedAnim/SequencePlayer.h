/* SequencePlayer.h
 * Plays LED animations on LEDs. 
 */

#ifndef LED_ANIM_SEQUENCEPLAYER_H
#define LED_ANIM_SEQUENCEPLAYER_H

#include <stdint.h>

class Led;
class LedAnim;

struct ActiveLight {
	Led* led;
	LedAnim* anim;
	uint16_t curIndex;  // index of last processed keyframe
	uint16_t elapsedTime;
};

class SequencePlayer {
public:
	SequencePlayer();
	void update();

	/* Stops all animations. */
	void stopAll();

	/* Continues all animations. */
	void resumeAll();
	//void addActiveLight(Led& led, Sequence& seq);
private:
	ActiveLight active_lights[20];
	bool isUpdating;
	uint8_t num_active_lights;
	unsigned long last_update_time;
};

#endif