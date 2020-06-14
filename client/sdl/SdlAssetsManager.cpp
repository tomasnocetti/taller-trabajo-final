#include "SdlAssetsManager.h"
#include <string>

SdlAssetsManager::SdlAssetsManager(SdlWindow& window) :
  window(window) {}

void SdlAssetsManager::addTexture(std::string id, const char* path) {
	LTexture* t = window.createTexture();
  t->loadFromFile(path);
  textures.emplace(id, t);
}

LTexture* SdlAssetsManager::getTexture(std::string id) {
	return textures[id];
}

SdlAssetsManager::~SdlAssetsManager() {
  for (auto &i : textures) {
    delete i.second;
  }
}
