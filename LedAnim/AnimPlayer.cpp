#include "AnimPlayer.h"
#include "Led.h"
#include "LedAnim.h"
#include "Arduino.h"

// 2^15 because IDs are 15 bits long
#define MAX_ID_SIZE 32768	

AnimPlayer::AnimPlayer()
  : isUpdating(true), numAnims(0), nextId(0)
{
  lastUpdateTime = millis();
}

void AnimPlayer::update() {
	// Caclulate delta time since last update()
	unsigned long curTime = millis();
	uint16_t deltaTime = curTime - lastUpdateTime;
	lastUpdateTime = curTime;

	if (!isUpdating) return;

	// Update each active animation
	for (uint8_t i = 0; i < numAnims; ++i) {
		AnimRecord& curRecord = animRecord[i];
		if (!curRecord.bIsPlaying) {
			continue;
		}

		// Calculate elapsed time since the last update to this record
		uint16_t elapsedTime = curRecord.elapsedTime + deltaTime;
		LedAnim* curAnim = curRecord.anim;

		// If the LedAnim is over, move to the next LedAnim
		if (curAnim->func.isOver(elapsedTime)) {
			LedAnim* next = curAnim->next;
			if (next) {
				curRecord.anim = next;
				elapsedTime = 0;
				curAnim = next;
			} else {
				removeRecord(i);
			}
		}

		// Call the update() function of the active LedAnim
		curAnim->func.update(elapsedTime);
		curRecord.elapsedTime = elapsedTime;
	}
}

uint16_t AnimPlayer::play(LedAnim& anim) {
	if (numAnims < MAX_ANIM) {
		AnimRecord& newRecord = animRecord[numAnims];
		newRecord.id = getNextId();
		newRecord.bIsPlaying = true;
		newRecord.anim = &anim;
		newRecord.elapsedTime = 0;
		numAnims++;
		return newRecord.id;
	} else {
		return MAX_ID_SIZE;		// will be an invalid ID
	}
}

void AnimPlayer::pause(uint16_t id) {
	for (uint8_t i = 0; i < numAnims; ++i) {
		if (animRecord[i].id == id) {
			animRecord[i].bIsPlaying = false;
		}
	}
}

void AnimPlayer::resume(uint16_t id) {
	for (uint8_t i = 0; i < numAnims; ++i) {
		if (animRecord[i].id == id) {
			animRecord[i].bIsPlaying = true;
		}
	}
}

void AnimPlayer::stop(uint16_t id) {
	for (uint8_t i = 0; i < numAnims; ++i) {
		if (animRecord[i].id == id) {
			removeRecord(i);
		}
	}
}

void AnimPlayer::pauseAll() {
	isUpdating = false;
}

void AnimPlayer::resumeAll() {
	isUpdating = true;
}

void AnimPlayer::stopAll() {
	numAnims = 0;
}

uint16_t AnimPlayer::getNextId() {
	uint16_t next = nextId;
	nextId = (nextId + 1) % MAX_ID_SIZE;
}

void AnimPlayer::removeRecord(uint8_t index) {
	if (index >= numAnims) {
		return;
	}
	if (index < numAnims - 1) {
		animRecord[index] = animRecord[numAnims - 1];
	}
	numAnims--;
}

#undef MAX_ID_SIZE
