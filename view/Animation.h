#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include "../sdl/LTexture.h"

#define FORWARD_ANIM_FRAMES 6
#define BACKWARD_ANIM_FRAMES 6
#define LEFT_ANIM_FRAMES 5
#define RIGHT_ANIM_FRAMES 5

class Animation {
public:
	Animation(std::string path, LTexture texture);
	void set(int currentAnim);
	void paint(int x, int y);
	Animation(const Animation&) = delete;
  Animation& operator=(const Animation&) = delete;

private:
	int index;
	LTexture texture;
	SDL_Rect forwardAnim[FORWARD_ANIM_FRAMES];
	SDL_Rect backwardAnim[BACKWARD_ANIM_FRAMES];
	SDL_Rect leftAnim[LEFT_ANIM_FRAMES];
	SDL_Rect rightAnim[RIGHT_ANIM_FRAMES];
	SDL_Rect lastFrame;

	void cropAnimationFrames();
};

#endif
