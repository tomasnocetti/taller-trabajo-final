#include "PlayerView.h"

PlayerView::PlayerView() {}

void PlayerView::init(int x, int y, LTexture texture){
	this->x = x;
	this->y = y;
	this->speed = 10;
	animation.init("client/assets/playerView.png", std::move(texture));
	animation.set(FORWARD_STAND);
}

void PlayerView::stand(int xOffset, int yOffset){
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
}

/*void PlayerView::paint(int cameraX, int cameraY){
	animation.paint(this->x - cameraX, this->y - cameraY);
}*/

void PlayerView::paint(const Camera &camera){
	animation.paint(this->x - camera.getX(), this->y - camera.getY());
}

int PlayerView::getX(){
	return this->x;
}

int PlayerView::getY(){
	return this->y;
}
