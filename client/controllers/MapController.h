#ifndef _MAP_CONTROLLER_H_
#define _MAP_CONTROLLER_H_

#include <string>
#include <vector>
#include "../model/ClientProxy.h"
#include "../sdl/LTexture.h"
#include "../sdl/SdlAssetsManager.h"
#include "../entities/Entity.h"

class MapController {
  public:
    MapController(ClientProxy& model, SdlAssetsManager& manager);
    ~MapController();
    void init();
    EntityList& getEntities();

  private:
    ClientProxy& model;
    SdlAssetsManager& manager;
    EntityList tiles;
    std::string texID;
    int mapScale;
};

#endif
