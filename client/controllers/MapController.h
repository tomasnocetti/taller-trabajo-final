#ifndef _MAP_CONTROLLER_H_
#define _MAP_CONTROLLER_H_

#include <string>
#include <vector>
//#include <memory>
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
    std::vector<LTexture*> textures;
    std::string texID;
    int mapScale;
};

#endif
