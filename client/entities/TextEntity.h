#ifndef _TEXT_ENTITY_H_
#define _TEXT_ENTITY_H_

#include <string>
#include <SDL2/SDL.h>
#include "Entity.h"
#include "../sdl/LTexture.h"
#include "../view/Camera.h"

class TextEntity : public Entity {
	private:
		LTexture* texture;
		TTF_Font* font;
		std::string previousText;
		int x;
		int y;
		
	public:
		TextEntity();
		TextEntity(const TextEntity&) = delete;
    TextEntity& operator=(const TextEntity&) = delete;
		void init(int x, int y, LTexture* texture, TTF_Font* font);
		void update(std::string text);
		void paint(const Camera &camera, 
			double scaleW, double scaleH) override {};
		void paint(double scaleW, double scaleH) override;
};

#endif
