#ifndef _LIFEV_H_
#define _LIFEV_H_

#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../view/Bar.h"

#define X 573
#define Y 433
#define W 217
#define H 137

#define BAR_X 628
#define BAR_W 106
#define BAR_H 11
#define MANA_BAR_Y 491
#define HEALTH_BAR_Y 542
#define MANA_TEX "client/assets/mana.png"
#define HEALTH_TEX "client/assets/health.png"

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
    void paint();
    void init(SdlWindow& window);
		//Deallocates memory
		~LifeViewport();
	private:
		Bar healthBar;
    Bar manaBar;
    //Entity gold;
};

#endif
