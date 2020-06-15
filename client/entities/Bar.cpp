#include "Bar.h"
#include <iostream>

Bar::Bar() {}

void Bar::init(LTexture* texture, int y) {
	this->texture = texture;
	this->destRect = {BAR_X, y, BAR_W, BAR_H};
}

void Bar::update(int value, int maxValue) {
	int aux = value;
	if(aux < 0)
		aux = 0;
	destRect.w = (aux * BAR_W) / maxValue;
}

void Bar::paint() {
	this->texture->paint(&destRect);
}
