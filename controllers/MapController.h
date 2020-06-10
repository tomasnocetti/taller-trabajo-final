#pragma once
#include <string>
#include <array>
#include <vector>
#include <memory>

#include "../sdl/SdlWindow.h"
#include "../sdl/LTexture.h"

#include "../entities/Entity.h"
#include <sstream>

class MapController {
  public:
    ~MapController();
    void init(SdlWindow& window);
    EntityList& getEntities();
  private:
    EntityList tiles;
    std::array<LTexture*, 10> textures;
    std::string texID;
    int mapScale;
};
