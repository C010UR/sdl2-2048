#pragma once

#include "SDL_pixels.h"

#include <vector>

class Config
{
  public:
    static inline int screenWidth             = 508;
    static inline int screenHeight            = 680;
    static inline int squareSize              = 80;
    static inline int padding                 = 12;
    static inline int squareRadius            = 10;
    static inline int fontSize                = 42;
    static inline int smallFontSize           = 24;
    static inline int squareNumber            = 4;
    static inline int scoreWidth              = 128;
    static inline int scoreHeight             = 72;
    static inline int scoreTextVerticalOffset = 16;
    static inline int glowAlpha               = 40;

    static inline SDL_Color backgroundColor     = {250, 248, 239, 255};
    static inline SDL_Color fontColor           = {119, 110, 101, 255};
    static inline SDL_Color gridBackgroundColor = {187, 173, 160, 255};
    static inline SDL_Color gridForegroundColor = {205, 193, 180, 255};

    struct BlockData
    {
        SDL_Color bgColor;
        SDL_Color fontColor;
        int       glow;
        bool      isSmallFont;
    };

    static inline std::vector<BlockData> blockData = {
        {{238, 228, 218, 255}, {119, 110, 101, 255}, 0, false},
        {{238, 225, 201, 255}, {119, 110, 101, 255}, 0, false},
        {{243, 178, 122, 255}, {250, 248, 239, 255}, 0, false},
        {{246, 150, 100, 255}, {250, 248, 239, 255}, 0, false},
        {{247, 124, 95, 255}, {250, 248, 239, 255}, 2, false},
        {{247, 95, 59, 255}, {250, 248, 239, 255}, 4, false},
        {{237, 208, 115, 255}, {250, 248, 239, 255}, 6, false},
        {{237, 204, 98, 255}, {250, 248, 239, 255}, 8, false},
        {{237, 201, 80, 255}, {250, 248, 239, 255}, 10, false},
        {{237, 201, 80, 255}, {250, 248, 239, 255}, 12, true},
        {{237, 201, 80, 255}, {250, 248, 239, 255}, 14, true},
        {{237, 201, 80, 255}, {250, 248, 239, 255}, 16, true},
        {{0, 0, 0, 255}, {250, 248, 239, 255}, 16, true},
    };
};