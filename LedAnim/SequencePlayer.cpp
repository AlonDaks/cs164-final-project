#include "SequencePlayer.h"
#include "Led.h"
#include "LedAnim.h"
#include "Arduino.h"

SequencePlayer::SequencePlayer()
  : isUpdating(true), numActiveLights(0)
{
  lastUpdateTime = millis();
}

void SequencePlayer::update() {
	unsigned long deltaTime = millis() - lastUpdateTime;



	/*for (int i = 0; i < this->num_active_lights; i++) {
	  ActiveLight *curLight = active_lights + i;
	  curLight->elapsedTime += deltaTime;
	  Sequence* seq = curLight->seq;
	  if (curLight->elapsedTime > seq->frames[curLight->curIndex].duration) {
	    curLight->curIndex++; // Move to the next KeyFrame
	  }
	  curLight->led->setValue(seq->frames[curLight->curIndex].value);
	}*/

	/*deltaTime = time since last call to update
	for each light in activeLights:
	  calculate color/brightness based on sequence keyframes
	  tell light to set values*/

}

void SequencePlayer::stopAll() {
	isUpdating = false;
}

void SequencePlayer::resumeAll() {
	isUpdating = true;
}

void SequencePlayer::play(Led& led, LedAnim& seq) {

}

void SequencePlayer::stop(Led& led) {
	for (int i = 0; i < MAX_LIGHTS; ++i) {
		//if ()
	}
}
