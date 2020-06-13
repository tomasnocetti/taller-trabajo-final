#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation() {
	forwardFrames = 6;
	backwardFrames = 6;
	leftFrames = 5;
	rightFrames = 5;
	this->path = "assets/playerView.png";
}

void PlayerAnimation::cropAnimationFrames() {
	for(int i = 0; i < forwardFrames; i++){
		 SDL_Rect frame = {i * 25, 0, 25, 48};
		 forwardAnim.push_back(frame);
	}

	for(int i = 0; i < backwardFrames; i++){
		SDL_Rect frame = {i * 25, 48, 25, 48};
		backwardAnim.push_back(frame);
	}

	for(int i = 0; i < leftFrames; i++){
		SDL_Rect frame = {i * 25, 93, 25, 48};
		leftAnim.push_back(frame);
	}

	for(int i = 0; i < rightFrames; i++){
		SDL_Rect frame = {i * 25, 144, 25, 48};
		rightAnim.push_back(frame);
	}
}
