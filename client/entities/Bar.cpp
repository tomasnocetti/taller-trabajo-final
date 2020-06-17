#include "Bar.h"

Bar::Bar() {}

void Bar::init(LTexture* texture, int y) {
	this->texture = texture;
	destRect = {BAR_X, y, BAR_W, BAR_H};
}

void Bar::update(int value, int maxValue) {
	int aux = value;
	if(aux < 0)
		aux = 0;
	destRect.w = (aux * BAR_W) / maxValue;
}

void Bar::paint(double scaleW, double scaleH) {
	texture->paint(destRect, scaleW, scaleH);
}
