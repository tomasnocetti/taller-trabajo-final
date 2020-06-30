#ifndef _INVENTORY_ENTITY_H_
#define _INVENTORY_ENTITY_H_

#include <string>
#include "Entity.h"
#include "../sdl/LTexture.h"
#include "TextEntity.h"

class InventoryEntity: public Entity {
  private:
    LTexture* texture;
    SDL_Rect destRect;
    TextEntity amountText;
    //TextEntity equippedText;
    LTexture* textTexture;
    TTF_Font* font;
    size_t amount;
    //bool isEquipped;
    LTexture* equipTexture = nullptr;

  public:
    InventoryEntity();
    void setImage(LTexture* background);
    void setTextAssetsAndInfo(LTexture* texture, 
      TTF_Font* font, size_t amount);
    //void setTextInfo(size_t amount, bool isEquipped);
    void setEquipTexture(LTexture* texture);
    void setRect(int x, int y, int w, int h) override;
    void paint(double scaleW, double scaleH) override;
    void paint(const Camera &camera, 
    	double scaleW, double scaleH) override {}
};

#endif
