#include "Shield.h"

Shield::Shield(LTexture* texture, int forwardX, int forwardY, int forwardW,
      int forwardH, int backX, int backY, int backW, int backH, int sideX,
      int sideY, int sideW, int sideH) {
		this->texture = texture;
		forward = {forwardX, forwardY, forwardW, forwardH};
    backward = {backX, backY, backW, backH};
    side = {sideX, sideY, sideW, sideH};	
}

void Shield::paint(int x, int y, double scaleW, double scaleH, 
	SDL_Rect* headFrame){
	if (texture == nullptr) return;

	/*
	headFrame.x == 0 -> camino para adelante
	headFrame.x == 16 -> camino para la derecha
	headFrame.x == 32 -> camino para la izquierda
	headFrame.x == 48 -> camino para atras
	*/

	if (headFrame->x == 0) {
    texture->paint(x, y + 5, scaleW, scaleH, &forward);
  } else if (headFrame->x == 48) {
		texture->paint(x, y + 5, scaleW, scaleH, &backward);
  } else if (headFrame->x == 32) {
		texture->paint(x, y + 5, scaleW, scaleH, &side);
  }
}
