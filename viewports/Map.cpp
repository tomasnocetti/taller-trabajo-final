#include "Map.h"

Map::Map(SdlWindow& window) :
  window(window),
  texture(window.createTexture()) {
  texture.loadFromFile("assets/static-image.jpg");
}

void Map::paint() {
  double hScale = window.getScaleHeightFactor();
  double wScale = window.getScaleWidthFactor();
  SDL_Rect mapViewport = {
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_MAP_X) * wScale)),
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_MAP_Y) * hScale)),
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_MAP_W) * wScale)),
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_MAP_H) * hScale))
  };
  SDL_RenderSetViewport(window.getRenderer(), &mapViewport);

  SDL_Rect camera = {
    0,
    0,
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_MAP_W) * wScale)),
    static_cast<int>(round(static_cast<double>(MAIN_SCREEN_BASE_MAP_H) * hScale))
  };
  texture.paint(0, 0, &camera);
}

Map::~Map() {}
