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

  void addTexture(const std::string& id, const char* path);
  void addTextTexture(const std::string& id);
  void addFont(const std::string& id, const std::string& path, int fontSize);
  void addMusic(const std::string& id, const std::string& path);
  void addSFX(const std::string& id, const std::string& path);
  TTF_Font* getFont(const std::string& id);
  LTexture* getTexture(const std::string& id);
  Mix_Music* getMusic(const std::string& id);
  Mix_Chunk* getSFX(const std::string& id);
  
private:
  std::map<std::string, LTexture*> textures;
  std::map<std::string, TTF_Font*> fonts;
  std::map<std::string, Mix_Music*> music;
  std::map<std::string, Mix_Chunk*> sfx;
  SdlWindow& window;
};

#endif
