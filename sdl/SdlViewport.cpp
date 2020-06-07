#include "SdlViewport.h"

SdlViewport::SdlViewport(
  SdlWindow& window,
  int x,
  int y,
  int w,
  int h,
  int scale) :
  window(window),
  scale(scale),
  srcViewport({x, y, w, h}) {}

void SdlViewport::fit() {
  double hScale = window.getScaleHeightFactor();
  double wScale = window.getScaleWidthFactor();
  destViewport = {
    static_cast<int>(
      round(static_cast<double>(srcViewport.x) * wScale)),
    static_cast<int>(
      round(static_cast<double>(srcViewport.y) * hScale)),
    static_cast<int>(
      round(static_cast<double>(srcViewport.w) * wScale)),
    static_cast<int>(
      round(static_cast<double>(srcViewport.h) * hScale))
  };
  SDL_RenderSetViewport(window.getRenderer(), &destViewport);
}

SdlViewport::~SdlViewport() {}
