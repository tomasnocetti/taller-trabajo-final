#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

#include "../model/ServerProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../view/PlayerView.h"
#include "../../DataDefinitions.h"
#include "../entities/Bar.h"
#include "../entities/TextEntity.h"
#include <vector>

class MainPlayerController {
  public:
  	MainPlayerController(ServerProxy& model, SdlAssetsManager& manager);
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
    void init();
    void update();
    ~MainPlayerController();
    void handleEvent(const SDL_Event &e, int cameraX, int cameraY);
    Entity &getEntity();
    std::vector<Entity*> getBars();

  private:
    ServerProxy& model;
    SdlAssetsManager& manager;
    PlayerView playerView;
    MovementData myMoveData;
    Bar healthBar;
    Bar manaBar;
    TextEntity gold;
    
    void checkRace(PlayerRace race);
};

#endif
