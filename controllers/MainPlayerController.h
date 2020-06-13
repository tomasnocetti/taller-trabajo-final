#ifndef _MAIN_PLAYER_CONTROLLER_H_
#define _MAIN_PLAYER_CONTROLLER_H_

#include "../view/PlayerView.h"
#include "../DataDefinitions.h"

class MainPlayerController {
  public:
  	MainPlayerController();
    MainPlayerController(const MainPlayerController&) = delete;
    MainPlayerController& operator=(const MainPlayerController&) = delete;
    MainPlayerController&& operator=(MainPlayerController&& other);
    void init(SdlWindow &window, int x, int y);
    ~MainPlayerController();
    void handleEvent(const SDL_Event &e);
    Entity &getEntity();

  private:
    //void move(int xOffset, int yOffset);
    //void attack();
    MainPlayerData data;
    PlayerView playerView;
};

#endif
