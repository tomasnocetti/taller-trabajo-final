#include <string>
#include "Animation.h"
#include "AnimationTypes.h"

Animation::Animation(std::string path, LTexture texture) : 
	texture(std::move(texture)) {
	this->texture.loadFromFile(path);
	this->index = 0;
	cropAnimationFrames();
}

void Animation::cropAnimationFrames(){
	for(int i = 0; i < FORWARD_ANIM_FRAMES; i++){
		forwardAnim[i] = {i * 25, 0, 25, 48};
	}

	for(int i = 0; i < BACKWARD_ANIM_FRAMES; i++){
		backwardAnim[i] = {i * 25, 48, 25, 48};
	}

	for(int i = 0; i < LEFT_ANIM_FRAMES; i++){
		leftAnim[i] = {i * 25, 93, 25, 48};
	}

	for(int i = 0; i < RIGHT_ANIM_FRAMES; i++){
		rightAnim[i] = {i * 25, 144, 25, 48};
	}
}

void Animation::set(int currentAnim){
	switch(currentAnim){
		case BACK_WALK:
			if(index >= BACKWARD_ANIM_FRAMES)
				index = 0;
			this->lastFrame = backwardAnim[index];
		break;
		case FORWARD_WALK:
			if(index >= FORWARD_ANIM_FRAMES)
				index = 0;
			this->lastFrame = forwardAnim[index];
		break;
		case LEFT_WALK:
			if(index >= LEFT_ANIM_FRAMES)
				index = 0;
			this->lastFrame = leftAnim[index];
		break;
		case RIGHT_WALK:
			if(index >= RIGHT_ANIM_FRAMES)
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
