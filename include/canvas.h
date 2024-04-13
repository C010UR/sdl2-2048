#pragma once

#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"

#include <string>

class Canvas
{
  public:
    static void init();

    static SDL_Texture *drawRectangle();
    static SDL_Texture *drawText(std::string message, TTF_Font &font, SDL_Color color);
};