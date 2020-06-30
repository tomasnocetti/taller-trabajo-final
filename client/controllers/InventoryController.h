#ifndef _INVENTORY_CONTROLLER_H_
#define _INVENTORY_CONTROLLER_H_

#include "../sdl/SdlAssetsManager.h"
#include "../model/ServerProxy.h"
#include "../entities/Entity.h"

class InventoryController {
  private:
    ServerProxy& model;
    SdlAssetsManager& manager;
    EntityList items;

    void generateImage(InventoryElementData item, int index);

  public:
    InventoryController(ServerProxy& model, SdlAssetsManager& manager);
    InventoryController(const InventoryController&) = delete;
    InventoryController& operator=(const InventoryController&) = delete;
    void update();
    void handleEvent(const SDL_Event& e);
    EntityList& getItems();
};

#endif
