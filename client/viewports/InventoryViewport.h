#ifndef _INVENTORY_VIEWPORT_H_
#define _INVENTORY_VIEWPORT_H_

#include <vector>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../entities/Entity.h"

#define INV_X 575
#define INV_Y 137
#define INV_W 213
#define INV_H 289

class InventoryViewport : public SdlViewport {
  public:
	  InventoryViewport(
      SdlWindow& window,
      int x = INV_X,
      int y = INV_Y,
      int w = INV_W,
      int h = INV_H);
    InventoryViewport(const InventoryViewport&) = delete;
    InventoryViewport& operator=(const InventoryViewport&) = delete;
    void paint(EntityList& items);
		~InventoryViewport();
};

#endif
