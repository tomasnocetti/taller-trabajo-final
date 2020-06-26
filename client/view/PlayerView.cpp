#include "PlayerView.h"
#include "AnimationTypes.h"
#include <iostream>

PlayerView::PlayerView() : headWear(HeadWear(nullptr, 0, 0, 0, 0)), 
	shield(Shield(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {}

void PlayerView::init(LTexture* texture) {
	this->x = 0;
	this->y = 0;
	animation = new PlayerAnimation(texture);
  animation->init();
	animation->set(FORWARD_STAND);
	headFrame = {0, 0, 16, 16};
	ghost = false;
}

void PlayerView::move(int x, int y){
	if(x == this->x && y < this->y){
		this->y = y;
		animation->set(BACK_WALK);
		headFrame = {48, 0, 16, 16};
	} else if (x == this->x && y > this->y){
			this->y = y;
			animation->set(FORWARD_WALK);
			headFrame = {0, 0, 16, 16};
	} else if (x < this->x && y == this->y){
			this->x = x;
			animation->set(LEFT_WALK);
			headFrame = {32, 0, 16, 16};
	} else if (x > this->x && y == this->y){
			this->x = x;
			animation->set(RIGHT_WALK);
			headFrame = {16, 0, 16, 16};
	} else if (x != this->x && y != this->y){
		this->x = x;
		this->y = y;
	}
}

void PlayerView::paint(const Camera &camera, double scaleW, double scaleH) {
	animation->paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH);

	if(head == nullptr) return;

	if(headFrame.x == 0 || headFrame.x == 48) {
		head->paint(x - camera.getX() + 3, y - camera.getY() - 9, 
			scaleW, scaleH, &headFrame);
	} else {
		head->paint(x - camera.getX(), y - camera.getY() - 10, 
			scaleW, scaleH, &headFrame);
	}

	headWear.paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH, &headFrame);

	shield.paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH, &headFrame);
}

void PlayerView::setHead(LTexture* head) {
	this->head = head;
}

void PlayerView::setHeadWear(HeadWear headWear){
	this->headWear = headWear;
}

void PlayerView::setBodyWear(LTexture* texture) {
	if (ghost) return;
	
	animation->changeTexture(texture);
}

void PlayerView::setShield(Shield shield){
	this->shield = shield;
}

void PlayerView::setGhostAnimation(LTexture* texture) {
	delete animation;
	this->animation = new GhostAnimation(texture);
	animation->init();
	animation->set(FORWARD_STAND);
	head = nullptr;
	ghost = true;
}

void PlayerView::setPlayerAnimation(LTexture* texture) {
	delete animation;
	this->animation = new PlayerAnimation(texture);
	animation->init();
	animation->set(FORWARD_STAND);
	ghost = false;
}

bool PlayerView::ghostState(){
	return ghost;
}

PlayerView::~PlayerView() {
	if(animation == nullptr) return;
	
  delete animation;
}
