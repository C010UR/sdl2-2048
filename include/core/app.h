#pragma once

#include "SDL_events.h"
#include "SDL_render.h"
#include "game_object.h"
#include "helper/logger.h"

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

class App
{
  private:
    int ups;
    int fps;

    bool isRunning = false;

    SDL_Window   *gWindow   = nullptr;
    SDL_Renderer *gRenderer = nullptr;

    std::vector<std::vector<GameObject>> gameObjects;

    Logger *logger = nullptr;

  public:
    App(Logger *logger, int ups = 60, int fps = -1);
    int  run();
    bool init();
    void handleEvent(SDL_Event *event);
    void update();
    void render();
    void clean();
};