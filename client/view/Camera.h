#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL2/SDL.h>

class Camera {
	private:
		SDL_Rect renderRect;

	public:
		Camera();
		void init(int x, int y, int w, int h);
		bool isInCameraRange(const SDL_Rect &destrect) const;
		void setX(int newX);
		void setY(int newY);
		int getX() const;
		int getY() const;
};

#endif
