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
  
  inventoryItem->setImage(manager.getTexture(
    "item_" + std::to_string(item.itemId)));

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
