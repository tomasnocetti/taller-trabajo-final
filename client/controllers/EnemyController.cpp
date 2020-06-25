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

void EnemyController::init() {} 

void EnemyController::update() {
	updateNPCs();
	updateOtherPlayers();
}

EntityList& EnemyController::getNPCs(){
	enemyVector.clear();
	std::vector<EnemyData> npcs = model.getNPCData();
	for(unsigned int i = 0; i < npcs.size(); i++){
		if(npcs[i].healthAndManaData.currentHP > 0){
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
		if(others[i].id != model.getMainPlayerData().id){
			if(otherPlayers.count(others[i].id) <= 0){
				LTexture* texture = manager.getTexture("clothes");
				std::shared_ptr<PlayerView> player(new PlayerView());
				player->init(texture);
				LTexture* head = checkRace(others[i].rootd.prace);
				player->setHead(head);
				otherPlayers.emplace(others[i].id, player);
			}
			otherPlayers.at(others[i].id)->move(others[i].position.x, 
				others[i].position.y);
			std::shared_ptr<PlayerView> player = 
				std::dynamic_pointer_cast<PlayerView>(otherPlayers.at(others[i].id));
			checkEquipment(player, others[i].equipment);
		}
	}

	std::vector<size_t> eraseVector;
	std::unordered_map<size_t, std::shared_ptr<Entity>>::iterator it;
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
  	otherPlayers.erase(eraseVector[i]);
  }
}

void EnemyController::checkEquipment(std::shared_ptr<PlayerView> playerView, 
	EquipmentData equipment){
  switch (equipment.body){
    case TUNIC:
      playerView->setBodyWear(manager.getTexture("blue-tunic"));
    break;
    case PLATE_ARMOR:
      playerView->setBodyWear(manager.getTexture("plate-armor"));
    break;
    case LEATHER_ARMOR:
      playerView->setBodyWear(manager.getTexture("leather-armor"));
    break;
    default:
      playerView->setBodyWear(manager.getTexture("clothes"));
    break;
  }

  switch (equipment.head){
    case HELMET:
      playerView->setHeadWear(HeadWear(manager.getTexture("helmet"), 
        3, -9, 0, -10));
    break;
    case HAT:
      playerView->setHeadWear(HeadWear(manager.getTexture("hat"), 
        3, -25, 0, -25));
    break;
    case HOOD:
      playerView->setHeadWear(HeadWear(manager.getTexture("hood"), 
        2, -10, -1, -10));
    break;
    default:
      playerView->setHeadWear(HeadWear(nullptr, 0, 0, 0, 0));
    break;
  }
}

EnemyController::~EnemyController() {}
