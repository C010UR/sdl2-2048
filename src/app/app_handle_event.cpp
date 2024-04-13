#include "SDL_events.h"
#include "app.h"

void App::handleEvent(SDL_Event *event) {
    if (event->type == SDL_EventType::SDL_QUIT) {
        this->isRunning = false;
        return;
    }
}