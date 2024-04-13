#pragma once

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"

#include <string>

class Canvas
{
  public:
    static inline TTF_Font *font = nullptr;

    static void init();

    static void drawRectangle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, SDL_Color color);
    static void drawText(SDL_Renderer *renderer, std::string *msg, SDL_Rect *rect, SDL_Color color);
};