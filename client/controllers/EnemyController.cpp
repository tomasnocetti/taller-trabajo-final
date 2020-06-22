#include "EnemyController.h"
#include "../view/EnemyView.h"
#include "../view/PlayerView.h"
#include "../view/SkeletonAnimation.h"
#include "../view/GoblinAnimation.h"
#include "../view/SpiderAnimation.h"
#include <vector>
#include <iostream>

EnemyController::EnemyController(
  ServerProxy& model,
  SdlAssetsManager& manager) : 
  model(model), manager(manager) {}

void EnemyController::init(){
  /** LOAD ASSETS ON INIT **/
  std::vector<EnemyData> v = model.getNPCData();
/*
  for (unsigned int i = 0; i < v.size(); i++){
  	Animation* animation = checkType(v[i].type);
  	enemies.emplace_back(
      new EnemyView(
        v[i].position.x,
        v[i].position.y,
  		  animation));
  }
*/
	std::vector<OtherPlayersData> others = model.getOtherPlayersData();
	for (unsigned int i = 0; i < others.size(); i++){
		LTexture* texture = manager.getTexture("clothes");
		PlayerView* player = new PlayerView();
		player->init(texture, others[i].position.x, others[i].position.y);
		LTexture* head = checkRace(others[i].rootd.prace);
		player->setHead(head);
		otherPlayers.emplace_back(player);
  }
}

void EnemyController::update() {
	std::vector<EnemyData> v = model.getNPCData();
	if(v.size() > enemies.size()) {
		unsigned int previousSize = enemies.size();
		enemies.reserve(v.size());
		for(unsigned int i = previousSize; i < v.size(); i++){
			Animation* animation = checkType(v[i].type);
			enemies.emplace_back(
      new EnemyView(
        v[i].position.x,
        v[i].position.y,
  		  animation));
		}
	}

	//para agregar otro jugador despues del inicio
	static int add = 0;
	std::vector<OtherPlayersData> others = model.getOtherPlayersData();
	if(others.size() > otherPlayers.size()) {
		unsigned int previousSize = otherPlayers.size();
		otherPlayers.reserve(v.size());
		for(unsigned int i = previousSize; i < others.size(); i++){
			LTexture* texture = manager.getTexture("plate-armor");
			PlayerView* player = new PlayerView();
			player->init(texture, others[i].position.x, others[i].position.y);
			LTexture* head = checkRace(others[i].rootd.prace);
			player->setHead(head);
			otherPlayers.emplace_back(player);
		}
	}

	for(unsigned int i = 0; i < others.size(); i++){
		//model.moveNPC(i, 1, 0);
		otherPlayers[i]->move(others[i].movement.xDir, others[i].movement.yDir, 
			others[i].movement.speed, others[i].movement.isMoving);
	}

	if(add == 100)
		model.add();
	
	add++;
}

EntityList& EnemyController::getNPCS(){
	return enemies;
}

EntityList& EnemyController::getOtherPlayers(){
	return otherPlayers;
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
    default:
			return nullptr;
    break;
  }
}

EnemyController::~EnemyController() {}
