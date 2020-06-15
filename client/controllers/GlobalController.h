#ifndef _GLOBAL_CONTROLLER_H_
#define _GLOBAL_CONTROLLER_H_

#include "../sdl/SdlAssetsManager.h"
#include "../model/ClientProxy.h"
#include "../../DataDefinitions.h"
#include "../entities/BackgroundEntity.h"

class GlobalController {
  public:
  	explicit GlobalController(ClientProxy& model, SdlAssetsManager& manager);
    GlobalController(const GlobalController&) = delete;
    GlobalController& operator=(const GlobalController&) = delete;
    void init();
    void handleEvent(const SDL_Event &e);
    EntityList &getEntities();

  private:
    ClientProxy& model;
    SdlAssetsManager& manager;
    EntityList screens;
};

#endif
