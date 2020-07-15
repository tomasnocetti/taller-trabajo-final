#include "TileEntity.h"
#include <string>

TileEntity::TileEntity(
  LTexture* stexture,
  int srcX,
  int srcY,
  int xpos,
  int ypos,
  int tsize,
  int tscale,
  std::string id
){
  texture = stexture;
	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = srcRect.h = tsize;
	destRect.x = static_cast<float>(xpos);
	destRect.y = static_cast<float>(ypos);
  destRect.w = destRect.h = tsize * tscale;
}

/*void TileEntity::paint(const Camera &camera, double scaleW, double scaleH){
  if (!camera.isInCameraRange(destRect.x, destRect.y)) return;

  texture->paint(destRect.x - camera.getX(),
    destRect.y - camera.getY(), scaleW, scaleH, &srcRect, 1);
}*/

void TileEntity::paint(const Camera &camera, double scaleW, double scaleH){
  texture->paint(destRect.x - camera.getX(),
    destRect.y - camera.getY(), scaleW, scaleH, &srcRect, 1);
}
