#include "Animation.h"
#include "AnimationTypes.h"
#include <SDL2/SDL.h>

Animation::Animation(LTexture* texture) :
  texture(texture) {}

void Animation::init(){
	/** Fill needed animation from SdlAssetsManager **/
	this->index = 0;
	cropAnimationFrames();
}

void Animation::cropAnimationFrames() {}

void Animation::set(int currentAnim){
	switch(currentAnim){
		case BACK_WALK:
			index = (SDL_GetTicks() / 125) % backwardFrames;
			this->lastFrame = backwardAnim[index];
		break;
		case FORWARD_WALK:
			index = (SDL_GetTicks() / 125) % forwardFrames;
			this->lastFrame = forwardAnim[index];
		break;
		case LEFT_WALK:
			index = (SDL_GetTicks() / 125) % leftFrames;
			this->lastFrame = leftAnim[index];
		break;
		case RIGHT_WALK:
			index = (SDL_GetTicks() / 125) % rightFrames;
			this->lastFrame = rightAnim[index];
		break;
		case BACK_STAND:
			this->lastFrame = backwardAnim[0];
		break;
		case FORWARD_STAND:
			this->lastFrame = forwardAnim[0];
		break;
		case LEFT_STAND:
			this->lastFrame = leftAnim[0];
	  break;
		case RIGHT_STAND:
			this->lastFrame = rightAnim[0];
		break;
	}
}

void Animation::paint(int x, int y){
	this->texture->paint(x, y, &this->lastFrame);
}

Animation::~Animation() {}
