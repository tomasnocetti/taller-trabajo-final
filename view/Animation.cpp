#include "Animation.h"

Animation::Animation(std::string path, SdlWindow &window) : 
	texture(window.createTexture()) {
	this->texture.loadFromFile(path);
	this->index = 0;
	cropAnimationFrames();
}

void Animation::cropAnimationFrames(){
	/*forwardAnim[0].x = 0;
	forwardAnim[1].x = 25;
	forwardAnim[2].x = 50;
	forwardAnim[3].x = 75;
	forwardAnim[4].x = 100;
	forwardAnim[5].x = 125;*/

	for(int i = 0; i < FORWARD_ANIM_FRAMES; i++){
		forwardAnim[i].x = i * 25;
		forwardAnim[i].y = 0;
		forwardAnim[i].w = 25;
		forwardAnim[i].h = 48;
	}

	for(int i = 0; i < BACKWARD_ANIM_FRAMES; i++){
		backwardAnim[i].x = i * 25;
		backwardAnim[i].y = 48;
		backwardAnim[i].w = 25;
		backwardAnim[i].h = 48;
	}

	for(int i = 0; i < LEFT_ANIM_FRAMES; i++){
		leftAnim[i].x = i * 25;
		leftAnim[i].y = 96;
		leftAnim[i].w = 25;
		leftAnim[i].h = 48;
	}

	for(int i = 0; i < RIGHT_ANIM_FRAMES; i++){
		rightAnim[i].x = i * 25;
		rightAnim[i].y = 144;
		rightAnim[i].w = 25;
		rightAnim[i].h = 48;
	}
}

void Animation::paint(int x, int y, char event){
	SDL_Rect frame;
	switch(event){
		case 'w':
			if(index >= FORWARD_ANIM_FRAMES)
				index = 0;
			frame = forwardAnim[index];
		break;
		case 's':
			if(index >= BACKWARD_ANIM_FRAMES)
				index = 0;
			frame = backwardAnim[index];
		break;
		case 'a':
			if(index >= LEFT_ANIM_FRAMES)
				index = 0;
			frame = leftAnim[index];
		break;
		case 'd':
			if(index >= RIGHT_ANIM_FRAMES)
				index = 0;
			frame = rightAnim[index];
		break;
		default:
		break;
	}
	index++;
	texture.paint(x, y, &frame);
}
