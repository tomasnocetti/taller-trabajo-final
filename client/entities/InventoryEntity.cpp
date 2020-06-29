#include "InventoryEntity.h"
#include <iostream>

#define INV_SLOT_W 62
#define INV_SLOT_H 71

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

void InventoryEntity::move(int x, int y) {
  destRect = {x, y, INV_SLOT_W, INV_SLOT_H};
}

void InventoryEntity::paint(double scaleW, double scaleH){
  texture->paint(destRect, scaleW, scaleH);
  amountText.init(destRect.x, destRect.y + 58, textTexture, font);
  amountText.update(std::to_string(amount));
  amountText.paint(scaleW, scaleH);
  
  if (equipTexture == nullptr) return;
  SDL_Rect equipRect = {destRect.x + 50, destRect.y - 15, 10, 10};
  equipTexture->paint(equipRect, scaleW, scaleH);
}
