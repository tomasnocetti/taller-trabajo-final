#include "Bar.h"

Bar::Bar() {}

void Bar::init(LTexture* texture, int y, LTexture* textTexture, 
	TTF_Font* font) {
	this->texture = texture;
	destRect = {BAR_X, y, BAR_W, BAR_H};
	text.init(BAR_X + 30, y - 1, textTexture, font);
}

void Bar::update(int value, int maxValue, int minValue) {
	if (maxValue == 0) {
		destRect.w = 0;
	} else {
		if (value < 0) value = 0;
		destRect.w = (value - minValue) * BAR_W / (maxValue - minValue);
	}
	text.update(std::to_string(value) + "/" + std::to_string(maxValue));
}

void Bar::paint(double scaleW, double scaleH) {
	texture->paint(destRect, scaleW, scaleH);
	text.center(BAR_X + BAR_W / 2);
	text.paint(scaleW, scaleH);
}
