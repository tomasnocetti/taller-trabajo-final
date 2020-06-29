#include "PlayerView.h"
#include "AnimationTypes.h"
#include "PlayerAnimation.h"
#include "GhostAnimation.h"
#include <iostream>

PlayerView::PlayerView(SdlAssetsManager& manager) : 
	manager(manager),
	headWear(HeadWear(nullptr, 0, 0, 0, 0)), 
	shield(Shield(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)), 
	weapon(Weapon(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0)) {}

void PlayerView::init() {
	this->x = 0;
	this->y = 0;
	LTexture* texture = manager.getTexture("clothes");
	animation.reset(new PlayerAnimation(texture));
  animation->init();
	animation->set(FORWARD_STAND);
	headFrame = {0, 0, 16, 16};
	ghost = false;
}

void PlayerView::move(int x, int y){
	if(x == this->x && y < this->y){
		this->y = y;
		animation->set(BACK_WALK);
		headFrame = {48, 0, 16, 16};
	} else if (x == this->x && y > this->y){
			this->y = y;
			animation->set(FORWARD_WALK);
			headFrame = {0, 0, 16, 16};
	} else if (x < this->x && y == this->y){
			this->x = x;
			animation->set(LEFT_WALK);
			headFrame = {32, 0, 16, 16};
	} else if (x > this->x && y == this->y){
			this->x = x;
			animation->set(RIGHT_WALK);
			headFrame = {16, 0, 16, 16};
	} else if (x != this->x && y != this->y){
		this->x = x;
		this->y = y;
	}
}

void PlayerView::paint(const Camera &camera, double scaleW, double scaleH) {
	animation->paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH);

	if(head == nullptr) return;

	if(headFrame.x == 0 || headFrame.x == 48) {
		head->paint(x - camera.getX() + 3, y - camera.getY() - 9, 
			scaleW, scaleH, &headFrame);
	} else {
		head->paint(x - camera.getX(), y - camera.getY() - 10, 
			scaleW, scaleH, &headFrame);
	}

	headWear.paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH, &headFrame);

	shield.paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH, &headFrame);

	weapon.paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH, &headFrame);
}

void PlayerView::checkRace(PlayerRace race) {
  if (ghost) return;

  switch (race) {
    case DWARF:
			head = manager.getTexture("dwarf-head");
    break;
    case ELF:
			head = manager.getTexture("elf-head");
    break;
    case HUMAN:
			head = manager.getTexture("human-head");
    break;
    case GNOME:
			head = manager.getTexture("gnome-head");
    break;
    default:
    break;
  }
}

void PlayerView::checkHealth(int health) {
  if (health <= 0 && !ghost) {
		animation.reset(new GhostAnimation(manager.getTexture("ghost")));
		animation->init();
		animation->set(FORWARD_STAND);
		head = nullptr;
		ghost = true;
  }

  if (health > 0 && ghost) {
		animation.reset(new PlayerAnimation(manager.getTexture("clothes")));
		animation->init();
		animation->set(FORWARD_STAND);
		ghost = false;
  }
}

void PlayerView::checkEquipment(EquipmentData equipment) {
  switch (equipment.body) {
    case TUNIC:
      setBodyWear(manager.getTexture("blue-tunic"));
    break;
    case PLATE_ARMOR:
      setBodyWear(manager.getTexture("plate-armor"));
    break;
    case LEATHER_ARMOR:
      setBodyWear(manager.getTexture("leather-armor"));
    break;
    default:
      setBodyWear(manager.getTexture("clothes"));
    break;
  }

  switch (equipment.head) {
    case HELMET:
			headWear = HeadWear(manager.getTexture("helmet"), 3, -9, 0, -10);
    break;
    case HAT:
			headWear = HeadWear(manager.getTexture("hat"), 3, -25, 0, -25);
    break;
    case HOOD:
			headWear = HeadWear(manager.getTexture("hat"), 2, -10, -1, -10);
    break;
    default:
			headWear = HeadWear(nullptr, 0, 0, 0, 0);
    break;
  }
  
  switch (equipment.leftHand) {
    case TURTLE_SHIELD:
			shield = Shield(manager.getTexture("turtle-shield"), 
        12, 14, 13, 18, 2, 60, 5, 17, 31, 104, 20, 16);
    break;
    case IRON_SHIELD:
			shield = Shield(manager.getTexture("iron-shield"), 
        6, 10, 17, 24, 1, 60, 13, 16, 25, 104, 24, 18);
    break;
    default:
			shield = Shield(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    break;
  }

  switch (equipment.rightHand) {
    case SIMPLE_BOW:
			weapon = Weapon(manager.getTexture("simple-bow"), 
        2, 6, 10, 20, 15, 56, 10, 14, 0, 141, 15, 15, 13, 5, 15, 10, 0, 5);
    break;
    case SWORD:
			weapon = Weapon(manager.getTexture("sword"), 
        34, 18, 17, 15, 44, 67, 4, 12, 9, 158, 13, 20, 17, 13, 20, 15, 2, 15);
    break;
    default:
			weapon = Weapon(nullptr, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    break;
  }
}

void PlayerView::setBodyWear(LTexture* texture) {
	if (ghost) return;
	
	animation->changeTexture(texture);
}

PlayerView::~PlayerView() {}
