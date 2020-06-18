#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL2/SDL.h>

class Camera {
	private:
		SDL_Rect renderRect;
		int maxWidth;
		int maxHeight;

	public:
		Camera();
		Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
		void init(int x, int y, int w, int h);
		void setMaxDimensions(int width, int height);
		bool isInCameraRange(int x, int y) const;
		void setX(int newX);
		void setY(int newY);
		int getX() const;
		int getY() const;
};

#endif
