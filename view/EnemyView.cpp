#include "EnemyView.h"
#include <iostream>

EnemyView::EnemyView(int x, int y, Animation *animation, SdlWindow &window) {
	this->x = x;
	this->y = y;
	this->speed = 10;
	this->animation = std::move(animation);
	animation->init(window);
	animation->set(FORWARD_STAND);
}

/*void EnemyView::init(int x, int y, Animation animation, SdlWindow &window){
	this->x = x;
	this->y = y;
	this->speed = 10;
	this->animation = animation;
	animation.init("assets/playerView.png", window);
	animation.set(FORWARD_STAND);
}*/

/*void PlayerView::stand(int xOffset, int yOffset){
	if(xOffset == 0 && yOffset < 0){
		animation.set(BACK_STAND);
	} else if (xOffset == 0 && yOffset > 0){
		animation.set(FORWARD_STAND);
	} else if (xOffset < 0 && yOffset == 0){
		animation.set(LEFT_STAND);
	} else if (xOffset > 0 && yOffset == 0){
		animation.set(RIGHT_STAND);
	}
}

void PlayerView::walk(int xOffset, int yOffset){
	if(xOffset == 0 && yOffset < 0){
		this->y += yOffset * speed;
		animation.set(BACK_WALK);
	} else if (xOffset == 0 && yOffset > 0){
		this->y += yOffset * speed;
		animation.set(FORWARD_WALK);
	} else if (xOffset < 0 && yOffset == 0){
		this->x += xOffset * speed;
		animation.set(LEFT_WALK);
	} else if (xOffset > 0 && yOffset == 0){
		this->x += xOffset * speed;
		animation.set(RIGHT_WALK);
	}

	if(this->x < 0)
		this->x = 0;
	if(this->y < 0)
		this->y = 0;
	if(this->x + 25 > 58 * 16)
		this->x = 58 * 16 - 25;
	if(this->y + 48 > 47 * 16)
		this->y = 47 * 16 - 48;
}*/

void EnemyView::paint(const Camera &camera){
	if(camera.isInCameraRange(this->x, this->y)){
		animation->paint(this->x - camera.getX(), this->y - camera.getY());
	}
}

EnemyView::~EnemyView(){
	delete this->animation;
}
