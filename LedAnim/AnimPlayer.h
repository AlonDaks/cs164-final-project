/* AnimPlayer.h
 * Plays LED animations. 
 */

#ifndef LED_ANIM_ANIMPLAYER_H
#define LED_ANIM_ANIMPLAYER_H

#include <stdint.h>

#define MAX_ANIM 4

class AnimNode;

struct AnimRecord {
	uint16_t id : 15;
	uint16_t bIsPlaying : 1;
	AnimNode* node;
	uint32_t elapsedMillis;
};

class AnimPlayer {
public:
	AnimPlayer();

	/* main update function */
	void update();
	
	/* Plays a particular animation. Returns an animation ID. */
	uint16_t play(AnimNode& animNode);

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

public:
	AnimRecord animRecord[MAX_ANIM];
	bool isUpdating;
	uint8_t numAnims;
	unsigned long lastUpdateTime;
	uint16_t nextId;

	/* Returns the next animation ID */
	uint16_t getNextId();

	/* */
	void incrementRecord(uint8_t index);

	/* Removes the i-th element */
	void removeRecord(uint8_t index);
};

#endif