#include "Global.h"

Global::Global(SdlWindow& window) :
  SdlViewport(
    window,
    MAIN_SCREEN_BASE_X,
    MAIN_SCREEN_BASE_Y,
    MAIN_SCREEN_BASE_W,
    MAIN_SCREEN_BASE_Global_H) {
}

void Global::paint(EntityList& entities) {
  fit();
  for (auto& e : entities) e->paint();
  // texture.paint(0, 0, &destViewport);
}



Global::~Global() {}
