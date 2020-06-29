#include "InventoryEntity.h"
#include <iostream>
InventoryEntity::InventoryEntity() {}

void InventoryEntity::setImage(LTexture* background) {
  texture = background;
}

void InventoryEntity::setTextAssetsAndInfo(LTexture* texture, 
  TTF_Font* font, size_t amount) {
  textTexture = texture;
  this->font = font;
  this->amount = amount;
}

void InventoryEntity::setEquipTexture(LTexture* texture){
  equipTexture = texture;
}

void InventoryEntity::setRect(int x, int y, int w, int h) {
  destRect = {x, y, w, h};
}

void InventoryEntity::paint(double scaleW, double scaleH){
  texture->paint(destRect, scaleW, scaleH);
  amountText.init(destRect.x, destRect.y + 58, textTexture, font);
  amountText.update(std::to_string(amount));
  amountText.paint(scaleW, scaleH);
  
  if(equipTexture == nullptr) return;
  SDL_Rect equipRect = {destRect.x + 50, destRect.y - 15, 10, 10};
  equipTexture->paint(equipRect, scaleW, scaleH);
}
