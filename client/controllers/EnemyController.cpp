#include "EnemyController.h"
#include "../view/EnemyView.h"
#include "../view/PlayerView.h"
#include "../view/SkeletonAnimation.h"
#include "../view/GoblinAnimation.h"
#include "../view/SpiderAnimation.h"
#include <vector>
#include <map>
#include <iostream>

EnemyController::EnemyController(
  ServerProxy& model,
  SdlAssetsManager& manager) : 
  model(model), manager(manager) {}

void EnemyController::init() {
	//aca me gustaria setear el ID, cosa que
	//no muestre al jugador principal como otro jugador
}

void EnemyController::update() {
	updateNPCs();
	updateOtherPlayers();
}

EntityList& EnemyController::getNPCs(){
	enemyVector.clear();
	std::vector<EnemyData> npcs = model.getNPCData();
	for(unsigned int i = 0; i < npcs.size(); i++){
		//if(npcs[i].points.currentHP > 0){
			enemyVector.emplace_back(enemies.at(npcs[i].id));
		//}
	}

  return enemyVector;
}

EntityList& EnemyController::getOtherPlayers(){
	otherPlayersVector.clear();
	std::map<size_t, std::shared_ptr<Entity>>::iterator it;
	for(it = otherPlayers.begin(); it != otherPlayers.end(); ++it) {
    otherPlayersVector.emplace_back(it->second);
  }

  return otherPlayersVector;
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

LTexture* EnemyController::checkRace(PlayerRace race) {
  switch (race){
    case DWARF:
      return manager.getTexture("dwarf-head");
    break;
    case ELF:
      return manager.getTexture("elf-head");
    break;
    case HUMAN:
      return manager.getTexture("human-head");
    break;
    case GNOME:
      return manager.getTexture("gnome-head");
    break;
    default:
			return nullptr;
    break;
  }
}

void EnemyController::updateNPCs(){
	std::vector<EnemyData> npcs = model.getNPCData();
	for(unsigned int i = 0; i < npcs.size(); i++){
		if(enemies.count(npcs[i].id) <= 0){
		Animation* animation = checkType(npcs[i].type);
		std::shared_ptr<EnemyView> enemy(new EnemyView(
			npcs[i].position.x, npcs[i].position.y, animation));
		enemies.emplace(npcs[i].id, enemy);
		}
		enemies.at(npcs[i].id)->move(npcs[i].position.x, npcs[i].position.y);
	}
}

void EnemyController::updateOtherPlayers(){
	std::vector<OtherPlayersData> others = model.getOtherPlayersData();
	for(unsigned int i = 0; i < others.size(); i++){
		if(otherPlayers.count(others[i].id) <= 0){
			//std::cout << "id: " << others[i].id << std::endl;
			LTexture* texture = manager.getTexture("plate-armor");
			std::shared_ptr<PlayerView> player(new PlayerView());
			player->init(texture, others[i].position.x, others[i].position.y);
			LTexture* head = checkRace(others[i].rootd.prace);
			player->setHead(head);
			otherPlayers.emplace(others[i].id, player);
		}
	otherPlayers.at(others[i].id)->move(others[i].position.x, 
		others[i].position.y);
	}

	std::vector<size_t> eraseVector;
	std::map<size_t, std::shared_ptr<Entity>>::iterator it;
	for(it = otherPlayers.begin(); it != otherPlayers.end(); ++it) {
		bool erase = true;
    for (unsigned int i = 0; i < others.size(); i++){
    	if(it->first == others[i].id){
    		erase = false;
    		break;
    	}
    }
    if (erase){
    	eraseVector.emplace_back(it->first);
    }
  }

  for (unsigned int i = 0; i < eraseVector.size(); i++){
  	enemies.erase(eraseVector[i]);
  }
}

EnemyController::~EnemyController() {}
