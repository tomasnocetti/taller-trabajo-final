#include "Camera.h"

#define TILE_SIZE 32

Camera::Camera() {}

void Camera::init(int x, int y, int w, int h){
	renderRect.x = x;
	renderRect.y = y;
	renderRect.w = w;
	renderRect.h = h;
}

void Camera::setMaxDimensions(int width, int height){
	maxWidth = width;
	maxHeight = height;
}

bool Camera::isInCameraRange(int x, int y) const {
	if(x >= renderRect.x - TILE_SIZE && 
		y >= renderRect.y - TILE_SIZE && 
		x <= renderRect.x + renderRect.w + TILE_SIZE &&
		y <= renderRect.y + renderRect.h + TILE_SIZE){
			return true;
	}
	return false;
}

void Camera::setX(int newX){
	renderRect.x = newX;

	if (renderRect.x < 0){
    renderRect.x = 0;
	}
  if (renderRect.x > maxWidth - renderRect.w){
    renderRect.x = maxWidth - renderRect.w;
  }
}

void Camera::setY(int newY){
	renderRect.y = newY;

	if (renderRect.y < 0){
    renderRect.y = 0;
	}
  if (renderRect.y > maxHeight - renderRect.h){
  	renderRect.y = maxHeight - renderRect.h;
  }
}

int Camera::getX() const {
	return renderRect.x;
}

int Camera::getY() const {
	return renderRect.y;
}
