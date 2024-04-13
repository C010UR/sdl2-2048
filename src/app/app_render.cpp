#include "app.h"

void App::render()
{
    if (SDL_RenderClear(this->gRenderer) < 0) {
        this->log(SDL_GetError(), App::LogLevel::ERROR);
        return;
    }

    for (unsigned layer = 0; layer < this->gameObjects.size(); layer++) {
        for (unsigned i = 0; i < this->gameObjects[layer].size(); i++) {
            this->gameObjects[layer][i].render();
        }
    }

    SDL_RenderPresent(this->gRenderer);
}