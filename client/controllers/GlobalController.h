#ifndef _GLOBAL_CONTROLLER_H_
#define _GLOBAL_CONTROLLER_H_

#include "../sdl/SdlAssetsManager.h"
#include "../model/ServerProxy.h"
#include "../../DataDefinitions.h"
#include "../entities/BackgroundEntity.h"

class GlobalController {
  public:
  	explicit GlobalController(ServerProxy& model, SdlAssetsManager& manager);
    GlobalController(const GlobalController&) = delete;
    GlobalController& operator=(const GlobalController&) = delete;
    void init();
    void update();
    void handleEvent(const SDL_Event &e);
    EntityList &getEntities();

  private:
    ServerProxy& model;
    SdlAssetsManager& manager;
    EntityList screens;
};

#endif
