#ifndef _ENEMY_CONTROLLER_H_
#define _ENEMY_CONTROLLER_H_

#include <vector>
#include "../model/ClientProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../../DataDefinitions.h"
#include "../view/Animation.h"
#include "../entities/Entity.h"

class EnemyController {
  public:
  	EnemyController(ClientProxy& model, SdlAssetsManager& manager);
    EnemyController(const EnemyController&) = delete;
    EnemyController& operator=(const EnemyController&) = delete;
    EnemyController&& operator=(EnemyController&& other);
  	void init();
    ~EnemyController();
    void update();
    EntityList& getEntity();

  private:
    //void move(int xOffset, int yOffset);
    //void attack();
    //std::vector<struct EnemyData> data;
    ClientProxy& model;
    SdlAssetsManager& manager;
    EntityList enemies;

    Animation* checkType(NPCClass type);
};

#endif
