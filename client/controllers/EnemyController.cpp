#include "EnemyController.h"
#include "../view/SkeletonAnimation.h"
#include <iostream>

EnemyController::EnemyController() {}

void EnemyController::init(SdlWindow &window, 
	std::vector<struct EnemyData>& data){
  for (unsigned int i = 0; i < data.size(); i++){
  	Animation* animation = checkType(data[i].type);
  	enemies.emplace_back(new EnemyView(data[i].x, data[i].y, 
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
}

EnemyController::~EnemyController() {}
