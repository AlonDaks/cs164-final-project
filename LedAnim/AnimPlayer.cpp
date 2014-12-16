#include "AnimPlayer.h"
#include "Led.h"
#include "AnimNode.h"
#include "Arduino.h"

// 2^15 because IDs are 15 bits long
#define MAX_ID_SIZE 32768	

AnimPlayer::AnimPlayer() 
: isUpdating(true), numAnims(0), nextId(0) {
	lastUpdateTime = millis();
}

void AnimPlayer::update() {
	// Caclulate delta time since last update()
	unsigned long curTime = millis();
	uint32_t deltaTime = curTime - lastUpdateTime;
	lastUpdateTime = curTime;

	if (!isUpdating) return;

	// Update each active animation
	for (uint8_t i = 0; i < numAnims; ++i) {
		AnimRecord& curRecord = animRecord[i];
		if (!curRecord.bIsPlaying) {
			continue;
		}

		// Calculate elapsed time since the last update to this record
		uint32_t elapsedMillis = curRecord.elapsedMillis + deltaTime;
		AnimNode* curAnim = curRecord.node;

		// If the AnimNode is over, move to the next AnimNode
		if (curAnim->isOver(elapsedMillis)) {
			AnimNode* next = curAnim->next();
			if (next) {
				curRecord.node = next;
				elapsedMillis = 0;
				curAnim = next;
			} else {
				removeRecord(i);
				--i;
				break;
			}
		}

		// Call the update() function of the active LedAnim
		curAnim->update(elapsedMillis);
		curRecord.elapsedMillis = elapsedMillis;
	}
}

uint16_t AnimPlayer::play(AnimNode& animNode) {
	if (numAnims < MAX_ANIM) {
		AnimRecord& newRecord = animRecord[numAnims];
		newRecord.id = getNextId();
		newRecord.bIsPlaying = true;
		newRecord.node = &animNode;
		newRecord.elapsedMillis = 0;
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
	uint16_t val = nextId;
	nextId = (nextId + 1) % MAX_ID_SIZE;
	return val;
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
