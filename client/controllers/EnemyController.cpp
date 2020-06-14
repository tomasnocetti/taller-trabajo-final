#include "EnemyController.h"
#include "../view/SkeletonAnimation.h"
#include "../view/GoblinAnimation.h"

EnemyController::EnemyController(ClientProxy& model) : model(model) {}

void EnemyController::init(SdlWindow &window){
	std::vector<struct EnemyData> v;
  struct EnemyData data;
  data.position.x = 100;
  data.position.y = 100;
  data.type = SKELETON;
  v.push_back(data);
  data.position.x = 600;
  data.position.y = 600;
  data.type = GOBLIN;
  v.push_back(data);
  for (unsigned int i = 0; i < v.size(); i++){
  	Animation* animation = checkType(v[i].type);
  	enemies.emplace_back(new EnemyView(v[i].position.x, v[i].position.y, 
  		std::move(animation), window));
  }
}

EntityList& EnemyController::getEntity(){
	return enemies;
}

Animation* EnemyController::checkType(NPCClass type){
	switch(type){
		case SKELETON:
			return std::move(new SkeletonAnimation());
		break;
		/*case ZOMBIE:
			return std::move(new ZombieAnimation());
		break;*/
		case GOBLIN:
			return std::move(new GoblinAnimation());
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
