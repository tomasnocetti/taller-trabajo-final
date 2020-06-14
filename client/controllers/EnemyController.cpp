#include "EnemyController.h"
#include "../view/SkeletonAnimation.h"
#include <iostream>

EnemyController::EnemyController(ClientProxy& model) : model(model) {}

void EnemyController::init(SdlWindow &window){
	std::vector<struct EnemyData> v;
  struct EnemyData data;
  data.x = 100;
  data.y = 100;
  data.type = 's';
  v.push_back(data);
  for (unsigned int i = 0; i < v.size(); i++){
  	Animation* animation = checkType(v[i].type);
  	enemies.emplace_back(new EnemyView(v[i].x, v[i].y, 
  		std::move(animation), window));
  }
}

EntityList& EnemyController::getEntity(){
	return enemies;
}

Animation* EnemyController::checkType(char type){
	switch(type){
		case 's':
			return std::move(new SkeletonAnimation());
		break;
		//case 'z':
			//enemyView.setAnimation(ZombieAnimation());
		//break;
	}
	return NULL;
}

EnemyController::~EnemyController() {}
