#include "Animation.h"
#include "AnimationTypes.h"
#include <SDL2/SDL.h>

Animation::Animation(LTexture* texture) :
  texture(texture) {}

void Animation::set(int currentAnim){
	switch(currentAnim){
		case BACK_WALK:
			index = (SDL_GetTicks() / 125) % backwardFrames;
			lastFrame = backwardAnim[index];
		break;
		case FORWARD_WALK:
			index = (SDL_GetTicks() / 125) % forwardFrames;
			lastFrame = forwardAnim[index];
		break;
		case LEFT_WALK:
			index = (SDL_GetTicks() / 125) % leftFrames;
			lastFrame = leftAnim[index];
		break;
		case RIGHT_WALK:
			index = (SDL_GetTicks() / 125) % rightFrames;
			lastFrame = rightAnim[index];
		break;
		case FORWARD_STAND:
			lastFrame = forwardAnim[0];
		break;
	}
}

void Animation::paint(int x, int y, double scaleW, double scaleH){
	texture->paint(x, y, scaleW, scaleH, &lastFrame);
}

Animation::~Animation() {}
