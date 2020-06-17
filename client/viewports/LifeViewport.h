#ifndef _LIFEV_H_
#define _LIFEV_H_

#include <vector>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../entities/Entity.h"

#define X 573
#define Y 433
#define W 217
#define H 137

class LifeViewport : SdlViewport{
	public:
		//Initializes variables
	  LifeViewport(
      SdlWindow& window,
      int x = X,
      int y = Y,
      int w = W,
      int h = H);
    LifeViewport(const LifeViewport&) = delete;
    LifeViewport& operator=(const LifeViewport&) = delete;
    void paint(std::vector<Entity*> values);
    void init();
		//Deallocates memory
		~LifeViewport();
};

#endif
