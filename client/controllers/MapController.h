#ifndef _MAP_CONTROLLER_H_
#define _MAP_CONTROLLER_H_

#include <string>
#include <vector>
#include "../model/ServerProxy.h"
#include "../sdl/LTexture.h"
#include "../sdl/SdlAssetsManager.h"
#include "../entities/Entity.h"
#include "../../definitions/PlayerDefinitions.h"

class MapController {
  public:
    MapController(ServerProxy& model, SdlAssetsManager& manager);
    ~MapController();
    void update();
    void updateDrops();
    EntityList& getEntities();
    EntityList& getDrops();

  private:
    void init();
    void generateDrop(DropItemData item);

    bool mapIsSet = false;
    ServerProxy& model;
    SdlAssetsManager& manager;
    EntityList tiles;
    EntityList drops;
    std::string texID;
    int mapScale;
};

#endif
