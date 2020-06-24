#include "Bar.h"

Bar::Bar() {}

void Bar::init(LTexture* texture, int y, LTexture* textTexture, 
	TTF_Font* font) {
	this->texture = texture;
	destRect = {BAR_X, y, BAR_W, BAR_H};
	text.init(BAR_X + 30, y - 1, textTexture, font);
}

void Bar::update(int value, int maxValue) {
	int aux = value;
	if(aux < 0)
		aux = 0;
	destRect.w = (aux * BAR_W) / maxValue;
	text.update(std::to_string(aux) + "/" + std::to_string(maxValue));
}

void Bar::paint(double scaleW, double scaleH) {
	texture->paint(destRect, scaleW, scaleH);
	text.paint(scaleW, scaleH);
}
