#include "core/app.h"
#include "core/config.h"
#include "helper/canvas.h"

bool App::init()
{
    this->logger->log("Initializing SDL", Logger::LogLevel::INFO);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        this->logger->log(SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    this->logger->log("Getting display information", Logger::LogLevel::INFO);

    SDL_DisplayMode gDisplayMode;

    if (SDL_GetDesktopDisplayMode(0, &gDisplayMode) < 0) {
        this->logger->log(SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    if (this->fps < 0) {
        this->fps = gDisplayMode.refresh_rate;
    }

    this->logger->log("Initializing the window", Logger::LogLevel::INFO);

    this->gWindow = SDL_CreateWindow(
        "2048",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Config::screenWidth,
        Config::screenHeight,
        SDL_WINDOW_SHOWN);

    if (this->gWindow == nullptr) {
        this->logger->log(SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    this->logger->log("Initializing the renderer", Logger::LogLevel::INFO);

    this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (this->gRenderer == nullptr) {
        this->logger->log(SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }
    
    this->logger->log("Initializing the canvas", Logger::LogLevel::INFO);
    Canvas::init();

    this->logger->log("Everything successfully initialized", Logger::LogLevel::INFO);
    return true;
}