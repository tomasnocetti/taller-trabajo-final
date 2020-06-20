#include "PlayerAnimation.h"
#include <iostream>
PlayerAnimation::PlayerAnimation(LTexture* texture) :
  Animation(texture) {
	forwardFrames = 6;
	backwardFrames = 6;
	leftFrames = 5;
	rightFrames = 5;
}

void PlayerAnimation::cropAnimationFrames() {
	for(int i = 0; i < forwardFrames; i++){
		 SDL_Rect frame = {2 + i * 25, 4, 21, 39};
		 forwardAnim.push_back(frame);
	}

	for(int i = 0; i < backwardFrames; i++){
		SDL_Rect frame = {i * 25, 48, 25, 48};
		backwardAnim.emplace_back(frame);
	}

	/*for(int i = 0; i < leftFrames; i++){
		SDL_Rect frame = {i * 25, 96, 25, 48};
		leftAnim.emplace_back(frame);
	}

	for(int i = 0; i < rightFrames; i++){
		SDL_Rect frame = {i * 25, 144, 25, 48};
		rightAnim.emplace_back(frame);
	}*/

	/*SDL_Rect frame = {2, 4, 21, 39};
	forwardAnim.emplace_back(frame);
	frame = {27, 4, 21, 39};
	forwardAnim.emplace_back(frame);
	frame = {52, 4, 21, 39};
	forwardAnim.emplace_back(frame);
	frame = {77, 4, 21, 39};
	forwardAnim.emplace_back(frame);
	frame = {102, 4, 21, 39};
	forwardAnim.emplace_back(frame);
	frame = {127, 4, 21, 39};
	forwardAnim.emplace_back(frame);*/

	SDL_Rect frame = {8, 94, 17, 39};
	leftAnim.emplace_back(frame);
	frame = {27, 94, 17, 39};
	leftAnim.emplace_back(frame);
	frame = {53, 94, 17, 39};
	leftAnim.emplace_back(frame);
	frame = {77, 94, 17, 39};
	leftAnim.emplace_back(frame);
	frame = {104, 94, 12, 39};
	leftAnim.emplace_back(frame);

	frame = {8, 139, 15, 39};
	rightAnim.emplace_back(frame);
	frame = {27, 139, 20, 39};
	rightAnim.emplace_back(frame);
	frame = {53, 139, 17, 39};
	rightAnim.emplace_back(frame);
	frame = {77, 139, 17, 39};
	rightAnim.emplace_back(frame);
	frame = {104, 139, 12, 39};
	rightAnim.emplace_back(frame);
}
