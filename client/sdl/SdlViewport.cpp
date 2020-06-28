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
  double hScale = window.getScaleHeightFactor();
  double wScale = window.getScaleWidthFactor();
  destViewport = sdlScaleRect(srcViewport, wScale, hScale);
  SDL_RenderSetViewport(window.getRenderer(), &destViewport);
}

double SdlViewport::getScaleWidthFactor(){
  return window.getScaleWidthFactor();
}

double SdlViewport::getScaleHeightFactor(){
  return window.getScaleHeightFactor();
}

SdlViewport::~SdlViewport() {}
