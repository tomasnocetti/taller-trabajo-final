#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

#include "../model/ClientProxy.h"
#include "../view/PlayerView.h"
#include "../../DataDefinitions.h"

class MainPlayerController {
  public:
  	explicit MainPlayerController(ClientProxy& model);
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
    void init(SdlWindow &window);
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
