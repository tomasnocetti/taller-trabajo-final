#include "InventoryController.h"
#include "../../definitions/PlayerDefinitions.h"
#include "../entities/InventoryEntity.h"
#include <iostream>
#include <string>
#include <vector>

InventoryController::InventoryController(ServerProxy& model, 
  SdlAssetsManager& manager) : model(model), manager(manager) {}

void InventoryController::update() {
  std::vector<InventoryElementData> inventory = 
    model.getMainPlayerData().inventory;

  items.clear();
  for (unsigned int i = 0; i < inventory.size(); i++){
    generateImage(inventory[i], i);
  }
}

void InventoryController::generateImage(InventoryElementData item, int index) {
  std::shared_ptr<InventoryEntity> inventoryItem(new InventoryEntity());
  switch (item.equipableType){
    case POTION:
      switch (item.enumPosition){
        case HEALTH:
          inventoryItem->setImage(manager.getTexture("health-potion"));
        break;
        case MANA:
          inventoryItem->setImage(manager.getTexture("mana-potion"));
        break;
      }
    break;
    case WEAPON:
      switch (item.enumPosition){
        case SWORD:
          inventoryItem->setImage(manager.getTexture("sword-inv"));
        break;
        case SIMPLE_BOW:
          inventoryItem->setImage(manager.getTexture("bow-inv"));
        break;
      }
    break;
    case BODY_ARMOUR:
      switch (item.enumPosition){
        case DEFAULT_B:
          inventoryItem->setImage(manager.getTexture("clothes-inv"));
        break;
        case TUNIC:
          inventoryItem->setImage(manager.getTexture("blue-tunic-inv"));
        break;
        case LEATHER_ARMOR:
          inventoryItem->setImage(manager.getTexture("leather-inv"));
        break;
        case PLATE_ARMOR:
          inventoryItem->setImage(manager.getTexture("plate-armor-inv"));
        break;
      }
    break;
    case LEFT_HAND_DEFENSE:
      switch (item.enumPosition){
        case TURTLE_SHIELD:
          inventoryItem->setImage(manager.getTexture("turtle-inv"));
        break;
        case IRON_SHIELD:
          inventoryItem->setImage(manager.getTexture("iron-shield-inv"));
        break;
      }
    break;
    case HEAD_DEFENSE:
      switch (item.enumPosition){
        case HELMET:
          inventoryItem->setImage(manager.getTexture("iron-helm-inv"));
        break;
        case HAT:
          inventoryItem->setImage(manager.getTexture("hat-inv"));
        break;
        case HOOD:
          inventoryItem->setImage(manager.getTexture("hood-inv"));
        break;
      }
    break;
  }

  std::string name = "invText_" + std::to_string(index + 1);
  inventoryItem->setTextAssetsAndInfo(manager.getTexture(name), 
    manager.getFont("arial"), item.amount);
    
  if (item.isEquiped) 
    inventoryItem->setEquipTexture(manager.getTexture("check"));

  items.emplace_back(inventoryItem);
}

EntityList& InventoryController::getItems() {
  return items;
}
