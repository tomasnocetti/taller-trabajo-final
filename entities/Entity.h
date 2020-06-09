#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../sdl/LTexture.h"


class Entity {
  public:
    virtual void paint() = 0;
    virtual void paint(int cameraX, int cameraY) = 0;
    virtual ~Entity() {}
};

using EntityList = std::vector<std::unique_ptr<Entity>>;

class TileEntity: public Entity {
  public:
    LTexture* texture;
    SDL_Rect srcRect, destRect;
    // Vector2D position;

	TileEntity(
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
  virtual ~TileEntity() {}
	void paint() override {
    texture->paint(destRect.x, destRect.y, &srcRect, 2);
	}

  void paint(int cameraX, int cameraY){
    texture->paint(destRect.x - cameraX, destRect.y - cameraY, &srcRect, 2);
  }
};
