#include "LifeViewport.h"
#include <vector>

LifeViewport::LifeViewport(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void LifeViewport::paint(std::vector<Entity*> values) {
  fit();

  for (unsigned int i = 0; i < values.size(); i++)
    values[i]->paint(wScale, hScale);
}

LifeViewport::~LifeViewport() {}
