#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include "../sdl/LTexture.h"
#include "../view/PlayerView.h"
#include "../DataDefinitions.h"

class MainPlayerController {
  public:
  	MainPlayerController();
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
  	void init(LTexture texture, int x, int y);
    ~MainPlayerController();
    //void init(int x, int y);
    void handleEvent(const SDL_Event &e);
    Entity &getEntity();

  private:
    //void move(int xOffset, int yOffset);
    //void attack();
    MainPlayerData data;
    PlayerView playerView;
};
