#include "SDL_error.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include "app.h"
#include "config.h"

bool App::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        this->log(SDL_GetError(), App::LogLevel::ERROR);
        return false;
    }

    SDL_DisplayMode gDisplayMode;

    if (SDL_GetDesktopDisplayMode(0, &gDisplayMode) < 0) {
        this->log(SDL_GetError(), App::LogLevel::ERROR);
        return false;
    }

    if (this->fps < 0) {
        this->fps = gDisplayMode.refresh_rate;
    }

    this->gWindow = SDL_CreateWindow(
        "2048",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Config::width,
        Config::height,
        SDL_WINDOW_SHOWN);

    if (this->gWindow == nullptr) {
        this->log(SDL_GetError(), App::LogLevel::ERROR);
        return false;
    }

    this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (this->gRenderer == nullptr) {
        this->log(SDL_GetError(), App::LogLevel::ERROR);
        return false;
    }

    if (SDL_SetRenderDrawColor(
            this->gRenderer,
            Config::backgroundColor.r,
            Config::backgroundColor.g,
            Config::backgroundColor.b,
            Config::backgroundColor.a)
        < 0) {
        this->log(SDL_GetError(), App::LogLevel::ERROR);
        return false;
    }

    this->log("SDL successfully initialized", App::LogLevel::INFO);
    return true;
}