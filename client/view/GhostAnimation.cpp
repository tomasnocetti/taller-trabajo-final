#include "GhostAnimation.h"

GhostAnimation::GhostAnimation(LTexture* texture) :
  Animation(texture) {
	forwardFrames = 5;
	backwardFrames = 5;
	leftFrames = 5;
	rightFrames = 5;
}

void GhostAnimation::cropAnimationFrames() {
	SDL_Rect frame = {14, 25, 17, 39};
	forwardAnim.emplace_back(frame);
	frame = {60, 22, 21, 43};
	forwardAnim.emplace_back(frame);
	frame = {106, 16, 22, 49};
	forwardAnim.emplace_back(frame);
	frame = {151, 9, 25, 56};
	forwardAnim.emplace_back(frame);
	frame = {199, 3, 26, 62};
	forwardAnim.emplace_back(frame);

  frame = {15, 91, 19, 38};
  backwardAnim.emplace_back(frame);
	frame = {61, 90, 47, 40};
	backwardAnim.emplace_back(frame);
	frame = {108, 90, 21, 45};
	backwardAnim.emplace_back(frame);
	frame = {154, 83, 22, 47};
	backwardAnim.emplace_back(frame);
	frame = {200, 77, 24, 53};
	backwardAnim.emplace_back(frame);

  frame = {16, 218, 21, 39};
  leftAnim.emplace_back(frame);
	frame = {63, 213, 23, 45};
	leftAnim.emplace_back(frame);
	frame = {108, 211, 26, 47};
	leftAnim.emplace_back(frame);
	frame = {154, 207, 26, 50};
	leftAnim.emplace_back(frame);
	frame = {200, 205, 28, 52};
	leftAnim.emplace_back(frame);

	frame = {10, 148, 21, 40};
	rightAnim.emplace_back(frame);
	frame = {56, 144, 22, 44};
	rightAnim.emplace_back(frame);
	frame = {102, 141, 25, 47};
	rightAnim.emplace_back(frame);
	frame = {150, 137, 26, 51};
	rightAnim.emplace_back(frame);
	frame = {196, 135, 28, 53};
	rightAnim.emplace_back(frame);
}
