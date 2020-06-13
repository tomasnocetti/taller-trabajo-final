#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

<<<<<<< HEAD
=======
#include "../model/ClientProxy.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
>>>>>>> f1d84ef7724ce3ec4352541424eb6be672b53fb2
#include "../view/PlayerView.h"
#include "../../DataDefinitions.h"

class MainPlayerController {
  public:
  	explicit MainPlayerController(ClientProxy& model);
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
    void init(SdlWindow &window, int x, int y);
    ~MainPlayerController();
    void handleEvent(const SDL_Event &e);
    Entity &getEntity();

  private:
    ClientProxy& model;
    //void move(int xOffset, int yOffset);
    //void attack();
    PlayerView playerView;
};

#endif
