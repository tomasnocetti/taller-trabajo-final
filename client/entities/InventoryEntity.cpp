#include "InventoryEntity.h"

InventoryEntity::InventoryEntity() {}

void InventoryEntity::setImage(LTexture* background) {
  texture = background;
}

/*void InventoryEntity::setTextAssets(LTexture* texture, TTF_Font* font){
  textTexture = texture;
  this->font = font;
}

void InventoryEntity::setTextInfo(size_t amount, bool isEquipped){
  this->amount = amount;
  this->isEquipped = isEquipped;
}*/

void InventoryEntity::setRect(int x, int y, int w, int h) {
  destRect = {x, y, w, h};
}

void InventoryEntity::paint(double scaleW, double scaleH){
  texture->paint(destRect, scaleW, scaleH);
  /*amountText.init(destRect.x + 10, destRect.y + 65, textTexture, font);
  amountText.update(std::to_string(amount));
  
  if(!isEquipped) return;
  equippedText.init(destRect.x + 65, destRect.y + 65, textTexture, font);
  equippedText.update("E");*/
}
