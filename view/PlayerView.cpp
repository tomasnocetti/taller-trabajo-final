#include "PlayerView.h"

PlayerView::PlayerView(int x, int y, SdlWindow &window) : 
	animation("assets/playerView.png", window) {
	this->x = x;
	this->y = y;
}

void PlayerView::moveX(int speed){
	this->x += speed;
	if(speed < 0){
		lastEvent = 'a';
	} else {
		lastEvent = 'd';
	}
}

void PlayerView::moveY(int speed){
	this->y += speed;
	if(speed < 0){
		lastEvent = 'w';
	} else {
		lastEvent = 's';
	}
}

void PlayerView::paint(){
	animation.paint(this->x, this->y, lastEvent);
}
