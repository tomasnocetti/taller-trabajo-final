#ifndef _EXP_VIEWPORT_H_
#define _EXP_VIEWPORT_H_

#include <vector>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../entities/Entity.h"

#define EXP_X 573
#define EXP_Y 27
#define EXP_W 217
#define EXP_H 73

class ExpViewport : public SdlViewport {
  public:
	  ExpViewport(
      SdlWindow& window,
      int x = EXP_X,
      int y = EXP_Y,
      int w = EXP_W,
      int h = EXP_H);
    ExpViewport(const ExpViewport&) = delete;
    ExpViewport& operator=(const ExpViewport&) = delete;
    void paint(std::vector<Entity*> values);
		~ExpViewport();
};

#endif
