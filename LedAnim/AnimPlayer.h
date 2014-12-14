/* AnimPlayer.h
 * Plays LED animations. 
 */

#ifndef LED_ANIM_AnimPlayer_H
#define LED_ANIM_AnimPlayer_H

#include <stdint.h>

#define MAX_ANIM 4

class LedAnim;

struct AnimRecord {
	uint16_t id : 15;
	uint16_t bIsPlaying : 1;
	LedAnim* anim;
	uint16_t elapsedTime;
};

class AnimPlayer {
public:
	AnimPlayer();

	/* main update function */
	void update();
	
	/* Plays a particular animation. Returns an animation ID. */
	uint16_t play(LedAnim& anim);

	/* Pauses an animation with the given animation ID if it exists. */
	void pause(uint16_t id);

	/* Resumes an animation with the given animation ID if it exists. */
	void resume(uint16_t id);

	/* Stops the animation with the animation ID. */
	void stop(uint16_t id);

	/* Pauses all animations. */
	void pauseAll();

	/* Resumes all animations. */
	void resumeAll();

	/* Stops all animations */
	void stopAll();

private:
	AnimRecord animRecord[MAX_ANIM];
	bool isUpdating;
	uint8_t numAnims;
	unsigned long lastUpdateTime;
	uint16_t nextId;

private:
	/* Returns the next animation ID */
	uint16_t getNextId();

	/* Removes the i-th element */
	void removeRecord(uint8_t index);
};

#endif