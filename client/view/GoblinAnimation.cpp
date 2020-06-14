#include "GoblinAnimation.h"

GoblinAnimation::GoblinAnimation(LTexture* texture) :
  Animation(texture) {
	forwardFrames = 8;
	backwardFrames = 8;
	leftFrames = 8;
	rightFrames = 8;
  cropAnimationFrames();
}

void GoblinAnimation::cropAnimationFrames() {
	for(int i = 0; i < forwardFrames; i++){
		 SDL_Rect frame = {i * 24, 0, 24, 33};
		 forwardAnim.push_back(frame);
	}

	for(int i = 0; i < backwardFrames; i++){
		SDL_Rect frame = {i * 24, 33, 24, 33};
		backwardAnim.push_back(frame);
	}

	for(int i = 0; i < leftFrames; i++){
		SDL_Rect frame = {i * 24, 66, 24, 33};
		leftAnim.push_back(frame);
	}

	for(int i = 0; i < rightFrames; i++){
		SDL_Rect frame = {i * 24, 99, 24, 33};
		rightAnim.push_back(frame);
	}
}
