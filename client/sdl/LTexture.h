#ifndef _LTEXTURE_H_
#define _LTEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class LTexture {
	public:
		//Initializes variables
		explicit LTexture(SDL_Renderer* renderer);
		LTexture();
    LTexture(const LTexture&) = delete;
    LTexture& operator=(const LTexture&) = delete;
    LTexture(LTexture&& other);
    LTexture& operator=(LTexture&& other);

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(std::string path);

		#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void paint(
      int x,
      int y,
      SDL_Rect* clip = NULL,
      int scale = 1,
      double angle = 0.0,
      SDL_Point* center = NULL,
      SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
    SDL_Renderer* renderer;
		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif
