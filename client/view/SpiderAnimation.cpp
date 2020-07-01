#include "SpiderAnimation.h"

SpiderAnimation::SpiderAnimation(LTexture* texture) :
  Animation(texture) {
	forwardFrames = 4;
	backwardFrames = 4;
	leftFrames = 4;
	rightFrames = 4;
	index = 0;
  cropAnimationFrames();
}

void SpiderAnimation::cropAnimationFrames() {
	for(int i = 0; i < forwardFrames; i++){
		 SDL_Rect frame = {i * 53, 0, 53, 35};
		 forwardAnim.push_back(frame);
	}

	for(int i = 0; i < backwardFrames; i++){
		SDL_Rect frame = {i * 53, 35, 53, 35};
		backwardAnim.push_back(frame);
	}

	SDL_Rect frame = {0, 71, 52, 33};
	leftAnim.push_back(frame);
	frame = {54, 70, 50, 34};
	leftAnim.push_back(frame);
	frame = {108, 71, 51, 33};
	leftAnim.push_back(frame);
	frame = {160, 73, 52, 31};
	leftAnim.push_back(frame);

	frame = {0, 105, 52, 34};
	rightAnim.push_back(frame);
	frame = {56, 105, 50, 34};
	rightAnim.push_back(frame);
	frame = {107, 105, 51, 34};
	rightAnim.push_back(frame);
	frame = {160, 105, 52, 33};
	rightAnim.push_back(frame);
}
