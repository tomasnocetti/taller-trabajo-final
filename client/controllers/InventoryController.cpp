#include "InventoryController.h"
#include "../../definitions/PlayerDefinitions.h"
#include "../entities/InventoryEntity.h"

#define KEYCODE_OFFSET 48
#define KEYCODE_1 49
#define KEYCODE_9 57

InventoryController::InventoryController(ServerProxy& model, 
  SdlAssetsManager& manager) : model(model), manager(manager) {}

void InventoryController::update() {
  std::vector<InventoryElementData> inventory = 
    model.getMainPlayerData().inventory;

  items.clear();
  for(unsigned int i = 0; i < inventory.size(); i++){
    generateImage(inventory[i]);
  }
}

void InventoryController::handleEvent(const SDL_Event &e) {
  if (e.type != SDL_KEYDOWN || 
    (e.key.keysym.sym < KEYCODE_1 || 
    e.key.keysym.sym > KEYCODE_9)) return;

  const char* keyName = SDL_GetKeyName(e.key.keysym.sym);
  int keyCode = static_cast<int>(*keyName);
  
  model.equip(keyCode - KEYCODE_OFFSET - 1);
}

void InventoryController::generateImage(InventoryElementData item) {
  std::shared_ptr<InventoryEntity> inventoryItem (new InventoryEntity());
  switch(item.equipableType){
    case POTION:
      switch(item.enumPosition){
        case HEALTH:
          inventoryItem->setImage(manager.getTexture("health-potion"));
        break;
        case MANA:
          inventoryItem->setImage(manager.getTexture("mana-potion"));
        break;
      }
    break;
    case WEAPON:
      switch(item.enumPosition){
        case SWORD:
          inventoryItem->setImage(manager.getTexture("sword-inv"));
        break;
        case SIMPLE_BOW:
          inventoryItem->setImage(manager.getTexture("bow-inv"));
        break;
        default:
        break;
      }
    break;
    case BODY_ARMOUR:
      switch(item.enumPosition){
        case DEFAULT_B:
          inventoryItem->setImage(manager.getTexture("clothes-inv"));
        break;
        /*case SIMPLE_BOW:
          inventoryItem->setImage(manager.getTexture("bow-inv"));
        break;*/
        default:
        break;
      }
    break;
    default:
    break;
  }
  /*inventoryItem->setTextAssets(manager.getTexture("expText"), 
    manager.getFont("arial"));
  inventoryItem->setTextInfo(item.amount, item.isEquiped);*/
  items.emplace_back(inventoryItem);
}

EntityList& InventoryController::getItems() {
  return items;
}