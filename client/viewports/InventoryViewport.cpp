#include "InventoryViewport.h"
#include <vector>
 
#define INV_ROW_LEN 3
#define INV_COL_LEN 3
#define INV_SLOT_W 62
#define INV_SLOT_H 71
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

      items[i * INV_ROW_LEN + j]->setRect(
        INV_SLOT_BASE_X + INV_SLOT_OFFSET_X * j, 
        INV_SLOT_BASE_Y + INV_SLOT_OFFSET_Y * i,
        INV_SLOT_W, INV_SLOT_H);

      items[i * INV_ROW_LEN + j]->paint(
        getScaleWidthFactor(), getScaleHeightFactor());
    }
  }
}

InventoryViewport::~InventoryViewport() {}
