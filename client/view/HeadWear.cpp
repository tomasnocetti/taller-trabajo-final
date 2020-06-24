#include "HeadWear.h"

IronHelmet::IronHelmet(LTexture* texture) : texture(texture) {}

void IronHelmet::paint(int x, int y, double scaleW, double scaleH, 
	SDL_Rect* headFrame){
	if(headFrame->x == 0 || headFrame->x == 48)
		texture->paint(x + 3, y - 9, scaleW, scaleH, headFrame);
	else
		texture->paint(x - 5, y - 10, scaleW, scaleH, headFrame);
}

MagicHat::MagicHat(LTexture* texture) : texture(texture) {}

void MagicHat::paint(int x, int y, double scaleW, double scaleH, 
	SDL_Rect* headFrame){
	if(headFrame->x == 0 || headFrame->x == 48)
		texture->paint(x + 3, y - 25, scaleW, scaleH, headFrame);
	else
		texture->paint(x - 5, y - 25, scaleW, scaleH, headFrame);
}