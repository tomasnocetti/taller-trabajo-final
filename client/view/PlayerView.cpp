#include "PlayerView.h"
#include "AnimationTypes.h"
#include "PlayerAnimation.h"
#include "GhostAnimation.h"

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
	animation->set(FORWARD_STAND);
	headFrame = {0, 0, 16, 16};
	ghost = false;
}

void PlayerView::move(int x, int y){
	if (x == this->x && y < this->y){
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
	if (!authenticated) return;

	animation->paint(x - camera.getX(), y - camera.getY(), 
		scaleW, scaleH);

	if (head == nullptr) return;

	if (headFrame.x == 0 || headFrame.x == 48) {
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
  }
}

void PlayerView::checkHealth(int health) {
  if (health <= 0 && !ghost) {
		animation.reset(new GhostAnimation(manager.getTexture("ghost")));
		animation->set(FORWARD_STAND);
		head = nullptr;
		ghost = true;
  }

  if (health > 0 && ghost) {
		animation.reset(new PlayerAnimation(manager.getTexture("clothes")));
		animation->set(FORWARD_STAND);
		ghost = false;
  }
}

void PlayerView::checkEquipment(EquipmentData equipment) {
  switch (equipment.body) {
    case 5:
      setBodyWear(manager.getTexture("blue-tunic"));
    break;
    case 10:
      setBodyWear(manager.getTexture("plate-armor"));
    break;
    case 9:
      setBodyWear(manager.getTexture("leather-armor"));
    break;
    default:
      setBodyWear(manager.getTexture("clothes"));
    break;
  }

  switch (equipment.head) {
    case 3:
			headWear = HeadWear(manager.getTexture("helmet"), 3, -9, 0, -10);
    break;
    case 7:
			headWear = HeadWear(manager.getTexture("hat"), 3, -25, 0, -25);
    break;
    case 8:
			headWear = HeadWear(manager.getTexture("hood"), 2, -10, -1, -10);
    break;
    default:
			headWear = HeadWear(nullptr, 0, 0, 0, 0);
    break;
  }
  
  switch (equipment.leftHand) {
    case 11:
			shield = Shield(manager.getTexture("turtle-shield"), 
        12, 14, 13, 18, 2, 60, 5, 17, 31, 104, 20, 16);
    break;
    case 4:
			shield = Shield(manager.getTexture("iron-shield"), 
        6, 10, 17, 24, 1, 60, 13, 16, 25, 104, 24, 18);
    break;
    default:
			shield = Shield(nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    break;
  }

  switch (equipment.rightHand) {
    case 1:
			weapon = Weapon(manager.getTexture("simple-bow"), 
        2, 6, 10, 20, 15, 56, 10, 14, 101, 139, 11, 29, 13, 5, 15, 10, 0, 0);
    break;
    case 2:
			weapon = Weapon(manager.getTexture("sword"), 
        34, 18, 17, 15, 0, 0, 0, 0, 9, 158, 13, 20, 17, 13, 18, 18, 2, 15);
    break;
		case 6:
			weapon = Weapon(manager.getTexture("ash-stick"), 
        4, 4, 4, 37, 17, 50, 4, 39, 51, 143, 20, 30, 16, 0, 18, 0, 0, 3);
    break;
		case 12:
			weapon = Weapon(manager.getTexture("gnarled-staff"), 
        4, 2, 4, 39, 17, 50, 4, 39, 51, 143, 23, 30, 16, 0, 17, 0, -2, 1);
    break;
		case 13:
			weapon = Weapon(manager.getTexture("elfic-flute"), 
        34, 27, 14, 11, 0, 0, 0, 0, 36, 164, 10, 6, 16, 15, 0, 0, 8, 17);
    break;
		case 14:
			weapon = Weapon(manager.getTexture("socketed-staff"), 
        4, 7, 12, 27, 66, 46, 7, 28, 8, 143, 15, 28, 13, 5, 19, 0, 3, 5);
    break;
		case 15:
			weapon = Weapon(manager.getTexture("axe"), 
        34, 18, 17, 15, 0, 0, 0, 0, 9, 158, 16, 20, 17, 13, 0, 0, 2, 15);	//18 18
    break;
		case 16:
			weapon = Weapon(manager.getTexture("mace"), 
        12, 20, 18, 18, 0, 0, 0, 0, 10, 143, 12, 21, 17, 13, 0, 0, 2, 15);
    break;
		case 17:
			weapon = Weapon(manager.getTexture("simple-bow"), 
        2, 6, 10, 20, 15, 56, 10, 14, 101, 139, 11, 29, 13, 5, 15, 10, 0, 0);
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

bool PlayerView::isAuthenticated() {
	return authenticated;
}

void PlayerView::authenticate() {
	authenticated = true;
}

PlayerView::~PlayerView() {}
