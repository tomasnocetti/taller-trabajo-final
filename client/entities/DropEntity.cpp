#include "DropEntity.h"

DropEntity::DropEntity(LTexture* texture, int x, int y, int w, int h) {
  this->texture = texture;
  destRect.x = x;
  destRect.y = y;
  destRect.w = w;
  destRect.h = h;
}

void DropEntity::move(int x, int y) {
  destRect.x = x;
  destRect.y = y;
}

void DropEntity::paint(const Camera& camera, double scaleW, double scaleH) {
  if (!camera.isInCameraRange(destRect.x, destRect.y)) return;

  move(destRect.x - camera.getX(), destRect.y - camera.getY());
  texture->paint(destRect, scaleW, scaleH);
}
