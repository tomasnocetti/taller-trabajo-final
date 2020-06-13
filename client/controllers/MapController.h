#pragma once
#include <string>
#include <array>
#include <vector>
#include <memory>

#include "../model/ClientProxy.h"
#include "../sdl/SdlWindow.h"
#include "../sdl/LTexture.h"

#include "../entities/Entity.h"

class MapController {
  public:
    explicit MapController(ClientProxy& model);
    ~MapController();
    void init(SdlWindow& window);
    EntityList& getEntities();

  private:
    ClientProxy& model;
    EntityList tiles;
    std::array<LTexture*, 10> textures;
    std::string texID;
    int mapScale;
};
