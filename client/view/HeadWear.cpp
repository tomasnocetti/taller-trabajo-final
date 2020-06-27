#include "HeadWear.h"

HeadWear::HeadWear(LTexture* texture, int xOffsetYAxis, int yOffsetYAxis, 
	int xOffsetXAxis, int yOffsetXAxis) {
		this->texture = texture;
		this->xOffsetYAxis = xOffsetYAxis;
		this->yOffsetYAxis = yOffsetYAxis;
		this->xOffsetXAxis = xOffsetXAxis;
		this->yOffsetXAxis = yOffsetXAxis;	
}

void HeadWear::paint(int x, int y, double scaleW, double scaleH, 
	SDL_Rect* headFrame){
	if(texture == nullptr) return;

	/*
	headFrame.x == 0 -> camino para adelante
	headFrame.x == 16 -> camino para la derecha
	headFrame.x == 32 -> camino para la izquierda
	headFrame.x == 48 -> camino para atras
	*/

	if(headFrame->x == 0 || headFrame->x == 48)
		texture->paint(x + xOffsetYAxis, y + yOffsetYAxis, 
		scaleW, scaleH, headFrame);
	else
		texture->paint(x + xOffsetXAxis, y + yOffsetXAxis, 
		scaleW, scaleH, headFrame);
}
