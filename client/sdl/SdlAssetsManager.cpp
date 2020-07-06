#include "SdlAssetsManager.h"
#include <string>

SdlAssetsManager::SdlAssetsManager(SdlWindow& window) :
  window(window) {}

void SdlAssetsManager::addTexture(std::string id, const char* path) {
	LTexture* t = window.createTexture();
  t->loadFromFile(path);
  textures.emplace(id, t);
}

void SdlAssetsManager::addTextTexture(std::string id) {
  LTexture* t = window.createTexture();
  textures.emplace(id, t);
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

void SdlAssetsManager::addMusic(std::string id, std::string path) {
  music.emplace(id, Mix_LoadMUS(path.c_str()));
}

Mix_Music* SdlAssetsManager::getMusic(std::string id){
  return music.at(id);
}

void SdlAssetsManager::addSFX(std::string id, std::string path) {
  sfx.emplace(id, Mix_LoadWAV(path.c_str()));
}

Mix_Chunk* SdlAssetsManager::getSFX(std::string id){
  return sfx.at(id);
}

SdlAssetsManager::~SdlAssetsManager() {
  for (auto &i : textures) {
    delete i.second;
  }
  for (auto &i : fonts) {
    TTF_CloseFont(i.second);
  }
  for (auto &i : music) {
    Mix_FreeMusic(i.second);
  }
  for (auto &i : sfx) {
    Mix_FreeChunk(i.second);
  }
}
