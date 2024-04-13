#pragma once

#include "SDL_pixels.h"

#include <vector>

class Config
{
  public:
    static inline int screenWidth    = 404;
    static inline int screenHeight   = 800;
    static inline int squareSize     = 80;
    static inline int padding        = 12;
    static inline int squareRounding = 5;

    static inline SDL_Color              backgroundColor     = {250, 248, 239, 255};
    static inline SDL_Color              fontColor           = {119, 110, 101, 255};
    static inline SDL_Color              gridBackgroundColor = {187, 173, 160, 255};
    static inline SDL_Color              gridForegroundColor = {205, 193, 180, 255};
    static inline std::vector<SDL_Color> powerColors         = {
        {238, 228, 218, 255},
        {238, 225, 201, 255},
        {243, 178, 122, 255},
        {246, 150, 100, 255},
        {247, 124, 95, 255},
        {247, 95, 59, 255},
        {237, 208, 115, 255},
        {237, 204, 98, 255},
        {237, 201, 80, 255},
        {237, 201, 80, 255},
        {237, 201, 80, 255},
        {237, 201, 80, 255},
    };
};