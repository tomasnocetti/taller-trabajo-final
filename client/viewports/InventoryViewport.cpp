#include "InventoryViewport.h"
#include <vector>
 
#define INV_ROW_LEN 3
#define INV_COL_LEN 3
#define INV_SLOT_BASE_X 6  
#define INV_SLOT_BASE_Y 23  
#define INV_SLOT_OFFSET_X 70
#define INV_SLOT_OFFSET_Y 95

InventoryViewport::InventoryViewport(SdlWindow& window, 
  int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void InventoryViewport::paint(EntityList& items) {
  fit();
  
  for (unsigned int i = 0; i < INV_ROW_LEN; i++){
    for (unsigned int j = 0; j < INV_COL_LEN; j++){
      if ((i * INV_ROW_LEN + j + 1) > items.size()) return;
      
      items[i * INV_ROW_LEN + j]->move(
        INV_SLOT_BASE_X + INV_SLOT_OFFSET_X * j, 
        INV_SLOT_BASE_Y + INV_SLOT_OFFSET_Y * i);
      
      items[i * INV_ROW_LEN + j]->paint(
        wScale, hScale);
    }
  }
}

InventoryViewport::~InventoryViewport() {}
