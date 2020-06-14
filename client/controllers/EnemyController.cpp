#include "EnemyController.h"
#include "../view/SkeletonAnimation.h"
#include "../view/GoblinAnimation.h"
#include <vector>

EnemyController::EnemyController(
  ClientProxy& model,
  SdlAssetsManager& manager) : 
  model(model), manager(manager) {}

void EnemyController::init(){
  /** LOAD ASSETS ON INIT **/
  manager.addTexture("skeleton-view", "client/assets/skeletonView.png");
  manager.addTexture("goblin-view", "client/assets/goblinView.png");

  std::vector<EnemyData> v = model.getNPCData();

  for (unsigned int i = 0; i < v.size(); i++){
  	Animation* animation = checkType(v[i].type);
  	enemies.emplace_back(
      new EnemyView(
        v[i].position.x,
        v[i].position.y,
  		  animation));
  }
}

EntityList& EnemyController::getEntity(){
	return enemies;
}

Animation* EnemyController::checkType(NPCClass type){
	switch(type){
		case SKELETON:
			return new SkeletonAnimation(
        manager.getTexture("skeleton-view"));
		break;
		/*case ZOMBIE:
			return std::move(new ZombieAnimation());
		break;*/
		case GOBLIN:
			return new GoblinAnimation(
        manager.getTexture("goblin-view"));
		break;
		/*case SPIDER:
			return std::move(new SpiderAnimation());
		break;*/
		default:
			return NULL;
		break;
	}
	return NULL;
}

EnemyController::~EnemyController() {}
