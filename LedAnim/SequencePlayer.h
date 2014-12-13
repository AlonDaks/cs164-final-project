/* SequencePlayer.h
 * Plays LED animations on LEDs. 
 */

#ifndef LED_ANIM_SEQUENCEPLAYER_H
#define LED_ANIM_SEQUENCEPLAYER_H

#include <stdint.h>

#define MAX_LIGHTS 5

class Led;
class LedAnim;

struct ActiveLight {
	Led& led;
	LedAnim& anim;
	uint16_t elapsedTime;
};

class SequencePlayer {
public:
	SequencePlayer();

	/* main update function */
	void update();

	/* Stops all animations. */
	void stopAll();

	/* Continues all animations. */
	void resumeAll();
	
	/* Plays a particular animation */
	void play(Led& led, LedAnim& seq);

	/* Stops the animation running on the specified LED */
	void stop(Led& led);
private:
	//ActiveLight activeLights[MAX_LIGHTS];
	bool isUpdating;
	uint8_t numActiveLights;
	unsigned long lastUpdateTime;
};

#endif