#ifndef _LOGIN_CONTROLLER_H_
#define _LOGIN_CONTROLLER_H_

#include "../sdl/SdlAssetsManager.h"
#include "../model/ClientProxy.h"
#include "../../DataDefinitions.h"
#include "../entities/BackgroundEntity.h"

#define MAIN_SCREEN_PATH "client/assets/main-screen.jpg"
#define LOGIN_SCREEN_PATH "client/assets/main-screens/login-screen.jpg"

class LoginController {
  public:
  	explicit LoginController(ClientProxy& model, SdlAssetsManager& manager);
    LoginController(const LoginController&) = delete;
    LoginController& operator=(const LoginController&) = delete;
    void init();
    void handleEvent(const SDL_Event &e);
    EntityList &getEntities();

  private:
    ClientProxy& model;
    SdlAssetsManager& manager;
    EntityList screens;
};

#endif
