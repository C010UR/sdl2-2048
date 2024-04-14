#include "SDL_keycode.h"
#include "core/app.h"

void App::handleEvent(SDL_Event *event)
{
    if (event->type == SDL_EventType::SDL_QUIT) {
        this->logger->log("App::handleEvent", "Catching Exit event", Logger::LogLevel::INFO);
        this->isRunning = false;
    } else if (event->type == SDL_EventType::SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_ESCAPE) {
            this->logger->log("App::handleEvent", "Catching Exit event", Logger::LogLevel::INFO);
            this->isRunning = false;
        } else if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_UP) {
            this->logger->log("App::handleEvent", "Catching up movement", Logger::LogLevel::INFO);
            this->moveUp();
        } else if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_LEFT) {
            this->logger->log("App::handleEvent", "Catching left movement", Logger::LogLevel::INFO);
            this->moveLeft();
        } else if (event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_DOWN) {
            this->logger->log("App::handleEvent", "Catching down movement", Logger::LogLevel::INFO);
            this->moveDown();
        } else if (event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_RIGHT) {
            this->logger->log("App::handleEvent", "Catching right movement", Logger::LogLevel::INFO);
            this->moveRight();
        } else if (event->key.keysym.sym == SDLK_r) {
            this->logger->log("App::handleEvent", "Catching restart", Logger::LogLevel::INFO);
            this->initBoard();
        }
    }
}