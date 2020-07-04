#ifndef __SDL_ASSET_MANAGER_H__
#define __SDL_ASSET_MANAGER_H__

#include "LTexture.h"
#include "SdlWindow.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <map>

class SdlAssetsManager {
public:
  explicit SdlAssetsManager(SdlWindow& window);
  SdlAssetsManager(const SdlAssetsManager&) = delete;
  SdlAssetsManager& operator=(const SdlAssetsManager&) = delete;
  ~SdlAssetsManager();

  void addTexture(std::string id, const char* path);
  void addTextTexture(std::string id);
  void addFont(std::string id, std::string path, int fontSize);
  void addMusic(std::string id, std::string path);
  void addSFX(std::string id, std::string path);
  TTF_Font* getFont(std::string id);
  LTexture* getTexture(std::string id);
  Mix_Music* getMusic(std::string id);
  Mix_Chunk* getSFX(std::string id);
  
private:
  std::map<std::string, LTexture*> textures;
  std::map<std::string, TTF_Font*> fonts;
  std::map<std::string, Mix_Music*> music;
  std::map<std::string, Mix_Chunk*> sfx;
  SdlWindow& window;
};

#endif
