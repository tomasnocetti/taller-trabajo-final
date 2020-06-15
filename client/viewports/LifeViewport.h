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

//#define BAR_X 628
//#define BAR_W 106
//#define BAR_H 11
//#define MANA_BAR_Y 491
//#define HEALTH_BAR_Y 542

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
