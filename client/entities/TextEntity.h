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

	public:
		TextEntity();
		TextEntity(const TextEntity&) = delete;
    TextEntity& operator=(const TextEntity&) = delete;
		void init(LTexture* texture, std::string initialText);
		void update(std::string text);
		void paint(const Camera &camera) override {};
		void paint() override;
};

#endif
