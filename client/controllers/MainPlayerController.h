#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

#include "../model/ClientProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../view/PlayerView.h"
#include "../../DataDefinitions.h"
#include "../entities/Bar.h"
#include "../entities/TextEntity.h"

class MainPlayerController {
  public:
  	MainPlayerController(ClientProxy& model, SdlAssetsManager& manager);
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
    void init();
    void update();
    ~MainPlayerController();
    void handleEvent(const SDL_Event &e);
    Entity &getEntity();
    std::vector<Entity*> getBars();

  private:
    ClientProxy& model;
    SdlAssetsManager& manager;
    PlayerView playerView;
    Bar healthBar;
    Bar manaBar;
    TextEntity gold;
};

#endif
