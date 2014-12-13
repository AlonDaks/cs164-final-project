#include "SequencePlayer.h"
#include "Led.h"
#include "LedAnim.h"
#include "Arduino.h"

SequencePlayer::SequencePlayer(){
  // Define pins for the LED display:
  num_active_lights = 0;
  last_update_time = millis();
}


/*void SequencePlayer::addActiveLight(Led& led, Sequence& seq){
  ActiveLight* al = active_lights + num_active_lights;
  //al->led = &led;
  //al->seq = &seq;
  al->curIndex = 0;
  al->elapsedTime= 0;
  this->num_active_lights++;
}*/

void SequencePlayer::update() {
    unsigned long deltaTime = millis() - last_update_time;

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
