#include "helper/canvas.h"  
#include "SDL2_gfxPrimitives.h"
#include "SDL_surface.h"
#include "core/config.h"

void Canvas::init()
{
    Canvas::font = TTF_OpenFont("assets/OpenSans-Regular.ttf", 32);
}

void Canvas::drawRectangle(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, SDL_Color color)
{
    roundedBoxRGBA(renderer, x1, y1, x2, y2, Config::squareRounding, color.r, color.g, color.b, color.a);
}

void Canvas::drawText(SDL_Renderer *renderer, std::string *msg, SDL_Rect *rect, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(Canvas::font, msg->c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, nullptr, rect);
    
    SDL_FreeSurface(surface);
}