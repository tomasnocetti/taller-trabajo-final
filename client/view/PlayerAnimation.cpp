#include "PlayerAnimation.h"

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

	frame = {0, 139, 15, 39};
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

void PlayerAnimation::changeTexture(LTexture* texture) {
	this->texture = texture;
}
