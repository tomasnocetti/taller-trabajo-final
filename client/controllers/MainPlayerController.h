#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

#include "../model/ServerProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../sdl/SdlUtils.h"
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
    void handleEvent(const SDL_Event &e, int cameraX, int cameraY);
    Entity &getEntity();
    std::vector<Entity*> getBars();
    std::vector<Entity*> getExp();
    ~MainPlayerController();

  private:
    bool active = true;
    ServerProxy& model;
    SDL_Rect src = {
      MAIN_SCREEN_BASE_MAP_X,
      MAIN_SCREEN_BASE_MAP_Y,
      MAIN_SCREEN_BASE_MAP_W,
      MAIN_SCREEN_BASE_MAP_H};
    SdlAssetsManager& manager;
    PlayerView playerView;
    Bar healthBar;
    Bar manaBar;
    TextEntity gold;
    TextEntity level;
    Bar expBar;

    void checkRace(PlayerRace race);
    void checkHealth(int health, PlayerRace race);
    void checkEquipment(EquipmentData equipment);
};

#endif
