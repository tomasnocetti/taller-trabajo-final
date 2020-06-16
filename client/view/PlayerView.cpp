#include "PlayerView.h"
#include "AnimationTypes.h"

PlayerView::PlayerView() {}

void PlayerView::init(LTexture* texture, int x, int y){
	this->x = x;
	this->y = y;
	animation = new PlayerAnimation(texture);
  animation->init();
	animation->set(FORWARD_STAND);
}

void PlayerView::stand(int xOffset, int yOffset){
	if(xOffset == 0 && yOffset < 0){
		animation->set(BACK_STAND);
	} else if (xOffset == 0 && yOffset > 0){
		animation->set(FORWARD_STAND);
	} else if (xOffset < 0 && yOffset == 0){
		animation->set(LEFT_STAND);
	} else if (xOffset > 0 && yOffset == 0){
		animation->set(RIGHT_STAND);
	}
}

void PlayerView::walk(int newX, int newY){
	int xOffset = x - newX;
	int yOffset = y - newY;
	if(xOffset == 0 && yOffset > 0){
		y = newY;
		animation->set(BACK_WALK);
	} else if (xOffset == 0 && yOffset < 0){
		y = newY;
		animation->set(FORWARD_WALK);
	} else if (xOffset > 0 && yOffset == 0){
		x = newX;
		animation->set(LEFT_WALK);
	} else if (xOffset < 0 && yOffset == 0){
		x = newX;
		animation->set(RIGHT_WALK);
	}

	/*if(this->x < 0)
		this->x = 0;
	if(this->y < 0)
		this->y = 0;
	if(this->x + 25 > 58 * 16)
		this->x = 58 * 16 - 25;
	if(this->y + 48 > 47 * 16)
		this->y = 47 * 16 - 48;*/
}

void PlayerView::paint(const Camera &camera, double scaleW, double scaleH){
	animation->paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH);
}

PlayerView::~PlayerView() {
  delete animation;
}
