#include "SdlAssetsManager.h"
#include <string>

SdlAssetsManager::SdlAssetsManager(SdlWindow& window) :
  window(window) {}

void SdlAssetsManager::addTexture(std::string id, const char* path) {
	LTexture* t = window.createTexture();
  t->loadFromFile(path);
  textures.emplace(id, t);
}

LTexture* SdlAssetsManager::createTexture() {
	return window.createTexture();
}

LTexture* SdlAssetsManager::getTexture(std::string id) {
	return textures[id];
}

void SdlAssetsManager::addFont(std::string id, std::string path, int fontSize) {
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* SdlAssetsManager::getFont(std::string id) {
	return fonts[id];
}

SdlAssetsManager::~SdlAssetsManager() {
  for (auto &i : textures) {
    delete i.second;
  }
  for (auto &i : fonts) {
    TTF_CloseFont(i.second);
  }
}
