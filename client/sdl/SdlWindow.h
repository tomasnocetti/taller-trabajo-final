#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include "LTexture.h"
#include "SdlUtils.h"
class SdlWindow {
public:
    /**
     * Ctor standalone
     */
    SdlWindow(int width, int height);
    SdlWindow(const SdlWindow&) = delete;
    SdlWindow& operator=(const SdlWindow&) = delete;
    ~SdlWindow();
    void fill();
    /** Este handler modifica al evento para adaptarlo a una escala real ! **/
    void handleEvent(SDL_Event& e);
    void fill(int r, int g, int b, int alpha);
    void render();
    void clear();
    LTexture* createTexture() const;
    double getScaleWidthFactor() const;
    double getScaleHeightFactor() const;
    SDL_Renderer* getRenderer() const;

private:
    int baseWidth;
    int baseHeight;
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
