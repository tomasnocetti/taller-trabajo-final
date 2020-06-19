#ifndef __SDL_ASSET_MANAGER_H__
#define __SDL_ASSET_MANAGER_H__

#include "LTexture.h"
#include "SdlWindow.h"
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>

class SdlAssetsManager {
public:
  explicit SdlAssetsManager(SdlWindow& window);
  SdlAssetsManager(const SdlAssetsManager&) = delete;
  SdlAssetsManager& operator=(const SdlAssetsManager&) = delete;
  ~SdlAssetsManager();

  void addTexture(std::string id, const char* path);
  void addFont(std::string id, std::string path, int fontSize);
  TTF_Font* getFont(std::string id);
  LTexture* getTexture(std::string id);

private:
  std::map<std::string, LTexture*> textures;
  std::map<std::string, TTF_Font*> fonts;
  SdlWindow& window;
};

#endif
