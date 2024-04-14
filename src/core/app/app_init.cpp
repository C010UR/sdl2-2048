#include "core/app.h"
#include "core/config.h"

#include <stdlib.h>
#include <time.h>

bool App::init()
{
    this->logger->log("App::init", "Initializing SDL", Logger::LogLevel::INFO);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    this->logger->log("App::init", "Initializing TTF", Logger::LogLevel::INFO);

    if (TTF_Init() < 0) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    this->logger->log("App::init", "Getting display information", Logger::LogLevel::INFO);

    SDL_DisplayMode gDisplayMode;

    if (SDL_GetDesktopDisplayMode(0, &gDisplayMode) < 0) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    if (this->fps < 0) {
        this->fps = gDisplayMode.refresh_rate;
    }

    this->logger->log("App::init", "Initializing the window", Logger::LogLevel::INFO);

    this->gWindow = SDL_CreateWindow(
        "2048",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        Config::screenWidth,
        Config::screenHeight,
        SDL_WINDOW_SHOWN);

    if (this->gWindow == nullptr) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    this->logger->log("App::init", "Initializing the renderer", Logger::LogLevel::INFO);

    this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (this->gRenderer == nullptr) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
        return false;
    }

    this->logger->log("App::init", "Initializing the font", Logger::LogLevel::INFO);
    this->font = TTF_OpenFont("assets/OpenSans-Bold.ttf", Config::fontSize);

    if (this->font == nullptr) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
    }

    this->smallFont = TTF_OpenFont("assets/OpenSans-Bold.ttf", Config::smallFontSize);

    if (this->smallFont == nullptr) {
        this->logger->log("App::init", SDL_GetError(), Logger::LogLevel::ERROR);
    }

    this->gridSize = Config::padding * 5 + Config::squareSize * 4;
    this->gridX    = (Config::screenWidth - this->gridSize) / 2;
    this->gridY    = Config::screenHeight - this->gridSize - Config::padding;

    this->initBoard();

    this->logger->log("App::init", "Everything successfully initialized", Logger::LogLevel::INFO);

    return true;
}

void App::initBoard()
{
    this->score = 0;

    srand(time(nullptr));

    this->blocks.clear();

    for (int i = 0; i < Config::squareSize; i++) {
        this->blocks.push_back(std::vector<int>(Config::squareSize, -1));
    }

    this->addBlock();
    this->addBlock();
}