#ifndef _MAP_CONTROLLER_H_
#define _MAP_CONTROLLER_H_

#include <string>
#include <vector>
#include "../sdl/SdlWindow.h"
#include "../sdl/LTexture.h"
#include "../entities/Entity.h"

class MapController {
  public:
    ~MapController();
    void init(SdlWindow& window);
    EntityList& getEntities();

  private:
    EntityList tiles;
    std::vector<LTexture*> textures;
    std::string texID;
    int mapScale;
};

#endif
