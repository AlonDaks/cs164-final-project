#include "LedAnim.h"

/******************************
 * LedAnim functions 
 ******************************/
LedAnim::LedAnim(AnimFunc& f) : func(f), next(nullptr) {}

void LedAnim::setNext(LedAnim& ledAnim) {
	next = &ledAnim;
}

void LedAnim::clearNext() {
	next = nullptr;
}

/******************************
 * FnAnim functions 
 ******************************/
/*FnAnim::FnAnim(AnimFunc& d) : delegate(d) {
	type = ANIM_FUNC;
}

uint16_t FnAnim::getDuration() {
	return delegate.durationInMillis();
}*/

/******************************
 * SeqAnim functions 
 ******************************/
/*SeqAnim::SeqAnim() : duration(0) {
	type = ANIM_SEQ;
}

uint16_t SeqAnim::getDuration() {
	return duration;
}*/
