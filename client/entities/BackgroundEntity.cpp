#include "BackgroundEntity.h"

BackgroundEntity::BackgroundEntity(
  LTexture* background
){
  texture = background;
}

void BackgroundEntity::paint(double scaleW, double scaleH){
  texture->paint(0, 0, scaleW, scaleH);
}
