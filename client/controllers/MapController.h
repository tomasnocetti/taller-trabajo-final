#ifndef _MAP_CONTROLLER_H_
#define _MAP_CONTROLLER_H_

#include <string>
#include <vector>
#include "../model/ServerProxy.h"
#include "../sdl/LTexture.h"
#include "../sdl/SdlAssetsManager.h"
#include "../entities/Entity.h"

class MapController {
  public:
    MapController(ServerProxy& model, SdlAssetsManager& manager);
    ~MapController();
    void update();
    EntityList& getEntities();

  private:
    void init();
    bool mapIsSet = false;
    ServerProxy& model;
    SdlAssetsManager& manager;
    EntityList tiles;
    std::string texID;
    int mapScale;
};

#endif
