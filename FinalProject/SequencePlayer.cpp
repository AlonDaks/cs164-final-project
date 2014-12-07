#include "SequencePlayer.h"

SequencePlayer::SequencePlayer(){
  // Define pins for the LED display:
  this->active_lights = ActiveLight[20]; //COMPLETE RESIZING / CHANGE INIT SIZE FROM 20 IF YOU WANT
  this->num_active_lights = 0;
  this->last_update_time = millis();
}


void SequencePlayer::addActiveLight(Led* led, Sequence* seq){
  ActiveLight al;
  al.led = led;
  al.seq = seq;
  al.curIndex = 0;
  al.elapsedTime= 0;
  active_lights[num_active_lights] = al;
  num_active_lights++;
}

void SequencePlayer::update() {
    unsigned long deltaTime = millis() - last_update_time;

    for (int i = 0; i < num_active_lights; i++) {
      ActiveLight curLight = active_lights[i];
      curLight.elapsedTime += deltaTime;
      Sequence seq = curLight.seq;
      if (elapsedTime > seq.frames[curLight.curIndex].duration) {
        curLight.curIndex++; // Move to the next KeyFrame
      }
      curLight.led.setValue(seq.frames[curLight.curIndex].value);
    }

    deltaTime = time since last call to update
    for each light in activeLights:
      calculate color/brightness based on sequence keyframes
      tell light to set values

}

struct ActiveLight {
  Led* led;
  Sequence* seq;
  uint curIndex;  // index of last processed keyframe
  uint elapsedTime;
};