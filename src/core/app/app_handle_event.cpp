#include "core/app.h"
#include <sstream>

void App::handleEvent(SDL_Event *event)
{
    if (event->type == SDL_EventType::SDL_QUIT) {
        this->logger->log("Catching Exit event", Logger::LogLevel::INFO);
        
        this->isRunning = false;
        return;
    }
}