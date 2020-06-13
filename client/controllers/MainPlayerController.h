#pragma once

#include "../model/ClientProxy.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/PlayerView.h"
#include "../../DataDefinitions.h"

class MainPlayerController {
  public:
  	explicit MainPlayerController(ClientProxy& model);
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
  	void init(LTexture texture, int x, int y);
    ~MainPlayerController();
    //void init(int x, int y);
    void handleEvent(const SDL_Event &e);
    Entity &getEntity();

  private:
    ClientProxy& model;
    //void move(int xOffset, int yOffset);
    //void attack();
    PlayerView playerView;
};
