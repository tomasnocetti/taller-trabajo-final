#include "EnemyView.h"

EnemyView::EnemyView(int x, int y, Animation *animation) {
	this->x = x;
	this->y = y;
	this->animation.reset(animation);
	animation->set(FORWARD_STAND);
}

void EnemyView::move(int x, int y) {
	if(x == this->x && y < this->y){
		this->y = y;
		animation->set(BACK_WALK);
	} else if (x == this->x && y > this->y){
		this->y = y;
		animation->set(FORWARD_WALK);
	} else if (x < this->x && y == this->y){
		this->x = x;
		animation->set(LEFT_WALK);
	} else if (x > this->x && y == this->y){
		this->x = x;
		animation->set(RIGHT_WALK);
	} else {
		this->x = x;
		this->y = y;
		animation->set(FORWARD_STAND);
	}
}

void EnemyView::paint(const Camera &camera, double scaleW, double scaleH){
	if (!camera.isInCameraRange(x, y)) return;

  animation->paint(x - camera.getX(), y - camera.getY(), 
  	scaleW, scaleH);
}

EnemyView::~EnemyView() {}
