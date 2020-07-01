#include "EnemyController.h"
#include "../view/EnemyView.h"
#include "../view/PlayerView.h"
#include "../view/SkeletonAnimation.h"
#include "../view/GoblinAnimation.h"
#include "../view/SpiderAnimation.h"
#include "../view/ZombieAnimation.h"
#include <vector>
#include <iostream>

EnemyController::EnemyController(
  ServerProxy& model,
  SdlAssetsManager& manager) : 
  model(model), manager(manager) {}

void EnemyController::update() {
	updateNPCs();
	updateOtherPlayers();
}

EntityList& EnemyController::getNPCs(){
	enemyVector.clear();
	std::vector<EnemyData> npcs = model.getNPCData();
	for(unsigned int i = 0; i < npcs.size(); i++){
		if (npcs[i].healthAndManaData.currentHP > 0){
			enemyVector.emplace_back(enemies.at(npcs[i].id));
		}
	}

  return enemyVector;
}

EntityList& EnemyController::getOtherPlayers(){
	otherPlayersVector.clear();
	std::unordered_map<size_t, std::shared_ptr<Entity>>::iterator it;
	for(it = otherPlayers.begin(); it != otherPlayers.end(); ++it) {
    otherPlayersVector.emplace_back(it->second);
  }

  return otherPlayersVector;
}

void EnemyController::updateNPCs(){
	std::vector<EnemyData> npcs = model.getNPCData();
	for(unsigned int i = 0; i < npcs.size(); i++){
		if(enemies.count(npcs[i].id) <= 0){
		std::shared_ptr<EnemyView> enemy(new EnemyView(
			npcs[i].position.x, npcs[i].position.y, checkType(npcs[i].type)));
		enemies.emplace(npcs[i].id, enemy);
		}
		enemies.at(npcs[i].id)->move(npcs[i].position.x, npcs[i].position.y);
	}
}

Animation* EnemyController::checkType(NPCClass type){
	switch(type){
		case SKELETON:
			return new SkeletonAnimation(
        manager.getTexture("skeleton-view"));
		break;
		case ZOMBIE:
			return new ZombieAnimation(
        manager.getTexture("zombie-view"));
		break;
		case GOBLIN:
			return new GoblinAnimation(
        manager.getTexture("goblin-view"));
		break;
		case SPIDER:
			return new SpiderAnimation(
        manager.getTexture("spider-view"));
		break;
		default:
			return NULL;
		break;
	}
	return NULL;
}

void EnemyController::updateOtherPlayers(){
	std::vector<OtherPlayersData> others = model.getOtherPlayersData();
	for(unsigned int i = 0; i < others.size(); i++){
		if(others[i].id != model.getMainPlayerData().id){
			if(otherPlayers.count(others[i].id) <= 0){
				std::shared_ptr<PlayerView> player(new PlayerView(manager));
				player->init();
				otherPlayers.emplace(others[i].id, player);
			}
			otherPlayers.at(others[i].id)->move(others[i].position.x, 
				others[i].position.y);
			std::shared_ptr<PlayerView> player = 
				std::dynamic_pointer_cast<PlayerView>(otherPlayers.at(others[i].id));
      player->checkRace(others[i].rootd.prace);
      player->checkHealth(others[i].healthAndMana.currentHP);
      player->checkEquipment(others[i].equipment);
		}
	}

	std::vector<size_t> eraseVector;
	std::unordered_map<size_t, std::shared_ptr<Entity>>::iterator it;
	for(it = otherPlayers.begin(); it != otherPlayers.end(); ++it) {
		bool erase = true;
    for (unsigned int i = 0; i < others.size(); i++){
    	if (it->first == others[i].id){
    		erase = false;
    		break;
    	}
    }
    if (erase){
    	eraseVector.emplace_back(it->first);
    }
  }

  for (unsigned int i = 0; i < eraseVector.size(); i++){
  	otherPlayers.erase(eraseVector[i]);
  }
}

EnemyController::~EnemyController() {}
