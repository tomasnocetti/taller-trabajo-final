#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

#include "../model/ServerProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../sdl/SdlUtils.h"
#include "../view/Camera.h"
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
    void handleEvent(const SDL_Event &e);
    Entity &getEntity();
    std::vector<Entity*> getBars();
    std::vector<Entity*> getExp();
    Camera& getCamera();
    ~MainPlayerController();

  private:
    bool active = true;
    bool cameraIsSet = false;
    ServerProxy& model;
    Camera camera;
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
    int lastSound = 0;

    void playSound();
};

#endif
