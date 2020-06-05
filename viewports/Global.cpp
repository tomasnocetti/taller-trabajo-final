#include "Global.h"

Global::Global(SdlWindow& window) :
  window(window),
  texture(window.createTexture()) {
  texture.loadFromFile(MAIN_SCREEN_PATH);
}

void Global::paint() {
  double hScale = window.getScaleHeightFactor();
  double wScale = window.getScaleWidthFactor();
  SDL_Rect globalViewport = {
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_X) * wScale)),
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_Y) * hScale)),
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_W) * wScale)),
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_Global_H) * hScale))
  };
  SDL_RenderSetViewport(window.getRenderer(), &globalViewport);

  texture.paint(0, 0, &globalViewport);
}

Global::~Global() {}
