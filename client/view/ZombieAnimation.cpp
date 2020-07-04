#include "ZombieAnimation.h"
#include <iostream>

ZombieAnimation::ZombieAnimation(LTexture* texture) :
  Animation(texture) {
	forwardFrames = 6;
	backwardFrames = 6;
	leftFrames = 5;
	rightFrames = 5;
	index = 0;
  cropAnimationFrames();
}

void ZombieAnimation::cropAnimationFrames() {
	for (int i = 0; i < forwardFrames; i++){
		SDL_Rect frame = {1 + i * 27, 0, 27, 64};
		forwardAnim.emplace_back(frame);
	}

	for (int i = 0; i < backwardFrames; i++){
		SDL_Rect frame = {1 + i * 27, 70, 27, 64};
		backwardAnim.emplace_back(frame);
	}

  SDL_Rect frame = {8, 140, 13, 64};
	leftAnim.emplace_back(frame);
  frame = {27, 140, 23, 64};
	leftAnim.emplace_back(frame);
  frame = {56, 140, 21, 64};
	leftAnim.emplace_back(frame);
  frame = {87, 140, 17, 64};
	leftAnim.emplace_back(frame);
  frame = {115, 140, 14, 64};
	leftAnim.emplace_back(frame);

  frame = {6, 212, 13, 64};
	rightAnim.emplace_back(frame);
  frame = {31, 212, 23, 64};
	rightAnim.emplace_back(frame);
  frame = {58, 212, 21, 64};
	rightAnim.emplace_back(frame);
  frame = {83, 212, 17, 64};
	rightAnim.emplace_back(frame);
  frame = {110, 212, 14, 64};
	rightAnim.emplace_back(frame);
}
