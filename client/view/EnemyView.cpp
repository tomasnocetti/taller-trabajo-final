#include "EnemyView.h"

EnemyView::EnemyView(int x, int y, Animation *animation) {
	this->x = x;
	this->y = y;
	this->animation = animation;
	animation->set(FORWARD_STAND);
}

void EnemyView::move(int xDir, int yDir, int speed, bool isMoving){
	if(isMoving){
		if(xDir == 0 && yDir < 0){
			y += yDir * speed;
			animation->set(BACK_WALK);
	} else if (xDir == 0 && yDir > 0){
			y += yDir * speed;
			animation->set(FORWARD_WALK);
	} else if (xDir < 0 && yDir == 0){
			x += xDir * speed;
			animation->set(LEFT_WALK);
	} else if (xDir > 0 && yDir == 0){
			x += xDir * speed;
			animation->set(RIGHT_WALK);
		}
	} else {
		if(xDir == 0 && yDir < 0){
				animation->set(BACK_STAND);
		} else if (xDir == 0 && yDir > 0){
				animation->set(FORWARD_STAND);
		} else if (xDir < 0 && yDir == 0){
				animation->set(LEFT_STAND);
		} else if (xDir > 0 && yDir == 0){
				animation->set(RIGHT_STAND);
		}
	}
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
