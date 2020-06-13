#ifndef _ENEMY_CONTROLLER_H_
#define _ENEMY_CONTROLLER_H_

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <vector>
#include "../view/EnemyView.h"
#include "../sdl/SdlWindow.h"
#include "../DataDefinitions.h"
#include "../view/Animation.h"

class EnemyController {
  public:
  	EnemyController();
    EnemyController(const EnemyController&) = delete;
    EnemyController& operator=(const EnemyController&) = delete;
    EnemyController&& operator=(EnemyController&& other);
  	void init(SdlWindow &window, std::vector <struct EnemyData>& data);
    ~EnemyController();
    //void init(int x, int y);
    void handleEvent(const SDL_Event &e);
    EntityList& getEntity();

  private:
    //void move(int xOffset, int yOffset);
    //void attack();
    //std::vector<struct EnemyData> data;
    //std::vector<EnemyView> enemies;
    EntityList enemies;

    Animation* checkType(char type);
};

#endif
