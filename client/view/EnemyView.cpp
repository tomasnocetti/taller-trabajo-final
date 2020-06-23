#include "EnemyView.h"

EnemyView::EnemyView(int x, int y, Animation *animation) {
	this->x = x;
	this->y = y;
	this->animation = animation;
	animation->set(FORWARD_STAND);
}

void EnemyView::move(int x, int y) {
	this->x = x;
	this->y = y;
}

void EnemyView::paint(const Camera &camera, double scaleW, double scaleH){
	if (!camera.isInCameraRange(x, y)) return;

  animation->paint(x - camera.getX(), y - camera.getY(), 
  	scaleW, scaleH);
}

EnemyView::~EnemyView(){
	if(animation == nullptr) return;
	
	delete animation;
}
