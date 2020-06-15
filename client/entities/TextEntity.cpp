#include "TextEntity.h"

TextEntity::TextEntity() {}

void TextEntity::init(LTexture* texture, std::string initialText) {
	this->texture = texture;
	SDL_Color white = {255, 255, 255, 255};
	this->texture->loadFromRenderedText(initialText, white);
}

void TextEntity::update(std::string text) {
	SDL_Color white = {255, 255, 255, 255};
	this->texture->loadFromRenderedText(text, white);
}

void TextEntity::paint(){
	int w, h;
	this->texture->queryTexture(w, h);
	SDL_Rect destRect = {115, 8, w, h};
	this->texture->paint(&destRect);
}
