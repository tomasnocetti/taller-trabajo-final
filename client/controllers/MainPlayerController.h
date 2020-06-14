#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

#include "../model/ClientProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../view/PlayerView.h"
#include "../../DataDefinitions.h"

class MainPlayerController {
  public:
  	MainPlayerController(ClientProxy& model, SdlAssetsManager& manager);
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
    void init();
    ~MainPlayerController();
    void handleEvent(const SDL_Event &e);
    Entity &getEntity();

  private:
    ClientProxy& model;
    SdlAssetsManager& manager;
    //void move(int xOffset, int yOffset);
    //void attack();
    PlayerView playerView;
};

#endif
