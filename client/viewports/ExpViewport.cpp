#include "ExpViewport.h"
#include <vector>

ExpViewport::ExpViewport(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void ExpViewport::paint(std::vector<Entity*> values) {
  fit();

  for (unsigned int i = 0; i < values.size(); i++)
    values[i]->paint(getScaleWidthFactor(), getScaleHeightFactor());
}

ExpViewport::~ExpViewport() {}
