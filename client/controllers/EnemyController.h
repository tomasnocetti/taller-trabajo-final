#ifndef _ENEMY_CONTROLLER_H_
#define _ENEMY_CONTROLLER_H_

#include <vector>
#include "../model/ServerProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../../DataDefinitions.h"
#include "../view/Animation.h"
#include "../entities/Entity.h"

class EnemyController {
  public:
  	EnemyController(ServerProxy& model, SdlAssetsManager& manager);
    EnemyController(const EnemyController&) = delete;
    EnemyController& operator=(const EnemyController&) = delete;
    EnemyController&& operator=(EnemyController&& other);
  	void init();
    ~EnemyController();
    void update();
    EntityList& getNPCS();
    EntityList& getOtherPlayers();

  private:
    ServerProxy& model;
    SdlAssetsManager& manager;
    EntityList enemies;
    EntityList otherPlayers;
    EntityList entities;

    Animation* checkType(NPCClass type);
    LTexture* checkRace(PlayerRace race);
};

#endif
