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
    /*TextEntity amountText;
    TextEntity equippedText;
    LTexture* textTexture;
    TTF_Font* font;
    size_t amount;
    bool isEquipped;*/

  public:
    InventoryEntity();
    void setImage(LTexture* background);
    /*void setTextAssets(LTexture* texture, TTF_Font* font);
    void setTextInfo(size_t amount, bool isEquipped);*/
    void setRect(int x, int y, int w, int h);
    void paint(double scaleW, double scaleH) override;
    void paint(const Camera &camera, 
    	double scaleW, double scaleH) override {}
};

#endif
