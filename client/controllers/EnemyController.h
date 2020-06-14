#ifndef _ENEMY_CONTROLLER_H_
#define _ENEMY_CONTROLLER_H_

#include <vector>
#include "../model/ClientProxy.h"
#include "../view/EnemyView.h"
#include "../sdl/SdlWindow.h"
#include "../../DataDefinitions.h"
#include "../view/Animation.h"

class EnemyController {
  public:
  	explicit EnemyController(ClientProxy& model);
    EnemyController(const EnemyController&) = delete;
    EnemyController& operator=(const EnemyController&) = delete;
    EnemyController&& operator=(EnemyController&& other);
  	void init(SdlWindow &window);
    ~EnemyController();
    void handleEvent(const SDL_Event &e);
    EntityList& getEntity();

  private:
    //void move(int xOffset, int yOffset);
    //void attack();
    //std::vector<struct EnemyData> data;
    EntityList enemies;
    ClientProxy& model;

    Animation* checkType(NPCClass type);
};

#endif
