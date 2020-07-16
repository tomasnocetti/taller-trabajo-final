#include "SdlViewport.h"
#include "SdlUtils.h"

SdlViewport::SdlViewport(
  SdlWindow& window,
  int x,
  int y,
  int w,
  int h,
  int scale) :
  window(window),
  srcViewport({x, y, w, h}) {}

void SdlViewport::fit() {
  hScale = window.getScaleHeightFactor();
  wScale = window.getScaleWidthFactor();
  destViewport = sdlScaleRect(srcViewport, wScale, hScale);
  SDL_RenderSetViewport(window.getRenderer(), &destViewport);
}

SdlViewport::~SdlViewport() {}
