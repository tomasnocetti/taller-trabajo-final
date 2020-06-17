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

void PlayerView::move(int xDir, int yDir, int speed){
	if(xDir == 0 && yDir < 0){
		y += yDir * speed;
		animation->set(BACK_WALK);
		headFrame = {48, 0, 16, 16};
	} else if (xDir == 0 && yDir > 0){
		y += yDir * speed;
		animation->set(FORWARD_WALK);
		headFrame = {0, 0, 16, 16};
	} else if (xDir < 0 && yDir == 0){
		x += xDir * speed;
		animation->set(LEFT_WALK);
		headFrame = {32, 0, 16, 16};
	} else if (xDir > 0 && yDir == 0){
		x += xDir * speed;
		animation->set(RIGHT_WALK);
		headFrame = {16, 0, 16, 16};
	} else if (xDir == 0 && yDir == 0){
		headFrame = {0, 0, 16, 16};
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
	head->paint(x - camera.getX() + 4, y - camera.getY() - 7, 
		scaleW, scaleH, &headFrame);
}

void PlayerView::setHead(LTexture* head) {
	this->head = head;
}

PlayerView::~PlayerView() {
  delete animation;
}
