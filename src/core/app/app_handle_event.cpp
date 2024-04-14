#include "SDL_keycode.h"
#include "core/app.h"

void App::handleEvent(SDL_Event *event)
{
    if (event->type == SDL_EventType::SDL_QUIT) {
        this->logger->log("App::handleEvent", "Catching Exit event", Logger::LogLevel::INFO);
        this->isRunning = false;
    } else if (event->type == SDL_EventType::SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_w) {
            this->logger->log("App::handleEvent", "Catching up movement", Logger::LogLevel::INFO);
            this->moveX = 0;
            this->moveY = 1;
        } else if (event->key.keysym.sym == SDLK_a) {
            this->logger->log("App::handleEvent", "Catching left movement", Logger::LogLevel::INFO);
            this->moveX = -1;
            this->moveY = 0;
        } else if (event->key.keysym.sym == SDLK_s) {
            this->logger->log("App::handleEvent", "Catching down movement", Logger::LogLevel::INFO);
            this->moveX = 0;
            this->moveY = -1;
        } else if (event->key.keysym.sym == SDLK_d) {
            this->logger->log("App::handleEvent", "Catching right movement", Logger::LogLevel::INFO);
            this->moveX = 1;
            this->moveY = 0;
        }
    }
}