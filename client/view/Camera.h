#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL2/SDL.h>

class Camera {
	private:
		SDL_Rect renderRect;
		int maxWidth;
		int maxHeight;
		int mapLayerTiles;
		int mapWidth;

	public:
		Camera();
		Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
		void init(int x, int y, int w, int h);
		void setMapConstants(int width, int tilewidth, int height, int tileheight);
		bool isInCameraRange(int x, int y) const;
		void setX(int newX);
		void setY(int newY);
		int getX() const;
		int getY() const;
		int getMapWidth() const;
		int getLayerTiles() const;
};

#endif
