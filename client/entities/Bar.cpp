#include "Bar.h"
#include <iostream>
#include <string>

Bar::Bar() {}

void Bar::init(SdlWindow& window, std::string path, 
	int x, int y, int w, int h) {
	// this->texture = window.createTexture();
	// this->texture.loadFromFile(path);
	this->destRect = {x, y, w, h};
	this->maxValueWidth = w;
}

void Bar::paint(int value, int maxValue) {
	int aux = value;
	if(aux < 0)
		aux = 0;
	destRect.w = (aux * maxValueWidth) / maxValue;
	// SDL_Rect clip = {0, 0, 40, 40};
	// this->texture.paint(&clip, destRect);
}
