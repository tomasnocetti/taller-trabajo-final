#include "SkeletonAnimation.h"

SkeletonAnimation::SkeletonAnimation() {
	forwardFrames = 5;
	backwardFrames = 5;
	leftFrames = 5;
	rightFrames = 5;
	this->path = "client/assets/skeletonView.png";
}

void SkeletonAnimation::cropAnimationFrames() {
	for(int i = 0; i < forwardFrames; i++){
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
	}
}
