#include "Animation.h"
#include "AnimationTypes.h"

Animation::Animation() {}

Animation::Animation(Animation&& other) {
  /*this->mTexture = other.mTexture;
  this->mWidth = other.mWidth;
  this->mHeight = other.mHeight;
  this->renderer = other.renderer;
  other.mTexture = NULL;
  other.renderer = NULL;*/
}

Animation& Animation::operator=(Animation&& other) {
  /*this->mTexture = other.mTexture;
  this->mWidth = other.mWidth;
  this->mHeight = other.mHeight;
  this->renderer = other.renderer;
  other.mTexture = NULL;
  other.renderer = NULL;*/
  return *this;
}

void Animation::init(SdlWindow &window){
	this->texture = window.createTexture();
	this->texture.loadFromFile(this->path);
	this->index = 0;
	cropAnimationFrames();
}

void Animation::cropAnimationFrames() {}

void Animation::set(int currentAnim){
	switch(currentAnim){
		case BACK_WALK:
			if(index >= backwardFrames)
				index = 0;
			this->lastFrame = backwardAnim[index];
		break;
		case FORWARD_WALK:
			if(index >= forwardFrames)
				index = 0;
			this->lastFrame = forwardAnim[index];
		break;
		case LEFT_WALK:
			if(index >= leftFrames)
				index = 0;
			this->lastFrame = leftAnim[index];
		break;
		case RIGHT_WALK:
			if(index >= rightFrames)
				index = 0;
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
	index++;
}

void Animation::paint(int x, int y){
	this->texture.paint(x, y, &this->lastFrame);
}

Animation::~Animation() {}
