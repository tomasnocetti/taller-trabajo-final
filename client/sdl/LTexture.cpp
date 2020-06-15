#include "LTexture.h"
#include <string>
#include <stdlib.h>
#include "SdlException.h"

LTexture::LTexture(SDL_Renderer* renderer) :
  renderer(renderer) {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::LTexture() {}

LTexture::LTexture(LTexture&& other) {
  this->mTexture = other.mTexture;
  this->mWidth = other.mWidth;
  this->mHeight = other.mHeight;
  this->renderer = other.renderer;
  other.mTexture = NULL;
  other.renderer = NULL;
}

LTexture& LTexture::operator=(LTexture&& other) {
  this->mTexture = other.mTexture;
  this->mWidth = other.mWidth;
  this->mHeight = other.mHeight;
  this->renderer = other.renderer;
  other.mTexture = NULL;
  other.renderer = NULL;
  return *this;
}

LTexture::~LTexture() {
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path) {
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf(
      "Unable to load image %s! SDL_image Error: %s\n",
      path.c_str(),
      IMG_GetError());
	} else {
		//Color key image
		SDL_SetColorKey(
      loadedSurface,
      SDL_TRUE,
      SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			printf(
        "Unable to create texture from %s! SDL Error: %s\n",
        path.c_str(), SDL_GetError());
		} else {
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(
  std::string textureText,
  SDL_Color textColor) {
	//Get rid of preexisting texture
	free();
	//no me abre si no le pongo el path absoluto, no se que onda
	TTF_Font* gFont = TTF_OpenFont("/home/lautaro/Escritorio/taller-trabajo-final/client/assets/a.ttf", 18);
	if(!gFont){
		throw SdlException("Error en la inicialización TTF", TTF_GetError());
	}
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended(
    gFont,
    textureText.c_str(),
    textColor);

	if (textSurface != NULL)
	{
		//Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL) {
			printf(
        "Unable to create texture from rendered text! SDL Error: %s\n",
        SDL_GetError());
		} else {
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	} else {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	TTF_CloseFont(gFont);
	//Return success
	return mTexture != NULL;
}

void LTexture::free() {
	//Free texture if it exists
	if (mTexture == NULL) return;

  SDL_DestroyTexture(mTexture);
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::queryTexture(int &w, int &h) {
	SDL_QueryTexture(this->mTexture, NULL, NULL, &w, &h);
}

void LTexture::paint(
  int x,
  int y,
  SDL_Rect* clip,
  int scale,
  double angle,
  SDL_Point* center,
  SDL_RendererFlip flip
) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x * scale, y * scale, mWidth, mHeight };

	//Set clip rendering dimensions
  if (clip != NULL) {
		renderQuad.w = clip->w * scale;
		renderQuad.h = clip->h * scale;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::paint(SDL_Rect* dest) {
	//Render to screen
	SDL_RenderCopy(renderer, mTexture, NULL, dest);
}

int LTexture::getWidth(){
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}
