#ifndef _LOGIN_CONTROLLER_H_
#define _LOGIN_CONTROLLER_H_

#include <SDL2/SDL_ttf.h>
#include "../sdl/SdlAssetsManager.h"
#include "../model/ServerProxy.h"
#include "../../DataDefinitions.h"
#include "../entities/BackgroundEntity.h"
#include "../entities/TextInputEntity.h"

class LoginController {
  public:
  	explicit LoginController(ServerProxy& model, SdlAssetsManager& manager);
    LoginController(const LoginController&) = delete;
    LoginController& operator=(const LoginController&) = delete;
    void init();
    void handleEvent(const SDL_Event &e);
    EntityList &getEntities();

  private:
    ServerProxy& model;
    SdlAssetsManager& manager;
    TextInputEntity* userInputField;
    EntityList screens;
};

#endif
