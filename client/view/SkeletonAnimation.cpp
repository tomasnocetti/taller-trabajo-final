#include "SkeletonAnimation.h"

SkeletonAnimation::SkeletonAnimation(LTexture* texture) :
  Animation(texture) {
	forwardFrames = 5;
	backwardFrames = 5;
	leftFrames = 5;
	rightFrames = 5;
  cropAnimationFrames();
}

void SkeletonAnimation::cropAnimationFrames() {
	/*for(int i = 0; i < forwardFrames; i++){
		 SDL_Rect frame = {i * 27, 0, 27, 48};
		 forwardAnim.push_back(frame);
	}

	for(int i = 0; i < backwardFrames; i++){
		SDL_Rect frame = {i * 27, 48, 27, 48};
		backwardAnim.push_back(frame);
	}

	for(int i = 0; i < leftFrames; i++){
		SDL_Rect frame = {i * 27, 96, 27, 48};
		leftAnim.push_back(frame);
	}

	for(int i = 0; i < rightFrames; i++){
		SDL_Rect frame = {i * 27, 144, 27, 48};
		rightAnim.push_back(frame);
	}*/

	SDL_Rect frame = {0, 0, 25, 47};
	forwardAnim.push_back(frame);
	frame = {29, 0, 21, 47};
	forwardAnim.push_back(frame);
	frame = {54, 0, 19, 47};
	forwardAnim.push_back(frame);
	frame = {80, 0, 20, 47};
	forwardAnim.push_back(frame);
	frame = {105, 0, 16, 47};
	forwardAnim.push_back(frame);

	frame = {0, 49, 21, 45};
	backwardAnim.push_back(frame);
	frame = {27, 51, 19, 43};
	backwardAnim.push_back(frame);
	frame = {52, 49, 22, 45};
	backwardAnim.push_back(frame);
	frame = {76, 51, 19, 43};
	backwardAnim.push_back(frame);
	frame = {104, 51, 17, 43};
	backwardAnim.push_back(frame);

	frame = {0, 96, 20, 45};
	rightAnim.push_back(frame);
	frame = {31, 98, 14, 43};
	rightAnim.push_back(frame);
	frame = {54, 96, 22, 45};
	rightAnim.push_back(frame);
	frame = {80, 98, 15, 43};
	rightAnim.push_back(frame);
	frame = {104, 97, 14, 44};
	rightAnim.push_back(frame);

	frame = {0, 143, 20, 45};
	leftAnim.push_back(frame);
	frame = {32, 145, 14, 43};
	leftAnim.push_back(frame);
	frame = {55, 144, 17, 44};
	leftAnim.push_back(frame);
	frame = {80, 144, 14, 44};
	leftAnim.push_back(frame);
	frame = {103, 143, 16, 45};
	leftAnim.push_back(frame);
}
