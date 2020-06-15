#ifndef __SDL_ASSET_MANAGER_H__
#define __SDL_ASSET_MANAGER_H__

#include "LTexture.h"
#include "SdlWindow.h"

#include <string>
#include <map>

class SdlAssetsManager {
public:
  explicit SdlAssetsManager(SdlWindow& window);
  SdlAssetsManager(const SdlAssetsManager&) = delete;
  SdlAssetsManager& operator=(const SdlAssetsManager&) = delete;
  ~SdlAssetsManager();

  void addTexture(std::string id, const char* path);
  LTexture* createTexture();
  LTexture* getTexture(std::string id);

private:
  std::map<std::string, LTexture*> textures;
  SdlWindow& window;
};

#endif
