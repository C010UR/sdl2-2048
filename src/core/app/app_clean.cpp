#include "core/app.h"

void App::clean()
{
    this->logger->log("Cleaning the SDL", Logger::LogLevel::INFO);

    SDL_DestroyWindow(this->gWindow);
    this->gWindow = nullptr;

    SDL_Quit();
}