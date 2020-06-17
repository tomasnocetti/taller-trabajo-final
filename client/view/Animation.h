#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <vector>
#include "../sdl/LTexture.h"
#include "../sdl/SdlWindow.h"

class Animation {
	public:
		explicit Animation(LTexture* texture);
		Animation(const Animation&) = delete;
	  Animation& operator=(const Animation&) = delete;
	  Animation(Animation&& other);
    Animation& operator=(Animation&& other);
		void init();
		void set(int currentAnim);
		void paint(int x, int y, double scaleW, double scaleH);
		virtual ~Animation();

	protected:
		int index;
		LTexture* texture;
		std::vector<SDL_Rect> forwardAnim;
		std::vector<SDL_Rect> backwardAnim;
		std::vector<SDL_Rect> leftAnim;
		std::vector<SDL_Rect> rightAnim;
		int forwardFrames, backwardFrames, leftFrames, rightFrames;
		SDL_Rect lastFrame;
		virtual void cropAnimationFrames();
};

#endif
