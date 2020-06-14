#include "BackgroundEntity.h"

BackgroundEntity::BackgroundEntity(
  LTexture* background
){
  texture = background;
}

void BackgroundEntity::paint(){
  texture->paint(0, 0);
}
