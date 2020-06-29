#ifndef _ENEMY_CONTROLLER_H_
#define _ENEMY_CONTROLLER_H_

#include <vector>
#include <unordered_map>
#include "../model/ServerProxy.h"
#include "../sdl/SdlAssetsManager.h"
#include "../../DataDefinitions.h"
#include "../view/Animation.h"
#include "../view/PlayerView.h"
#include "../entities/Entity.h"

class EnemyController {
  public:
  	EnemyController(ServerProxy& model, SdlAssetsManager& manager);
    EnemyController(const EnemyController&) = delete;
    EnemyController& operator=(const EnemyController&) = delete;
    EnemyController&& operator=(EnemyController&& other);
  	void init();
    void update();
    EntityList& getNPCs();
    EntityList& getOtherPlayers();
    ~EnemyController();

  private:
    size_t id;
    ServerProxy& model;
    SdlAssetsManager& manager;
    EntityList enemyVector;
    EntityList otherPlayersVector;
    std::unordered_map<size_t, std::shared_ptr<Entity>> enemies;
    std::unordered_map<size_t, std::shared_ptr<Entity>> otherPlayers;

    Animation* checkType(NPCClass type);
    void updateNPCs();
    void updateOtherPlayers();
};

#endif
