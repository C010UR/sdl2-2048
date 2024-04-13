#include "SDL_video.h"
#include "app.h"

void App::clean() {
    SDL_DestroyWindow(this->gWindow);
    this->gWindow = nullptr;

    SDL_Quit();
}