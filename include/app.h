#pragma once

#include "SDL_events.h"
#include "SDL_render.h"
#include "game_object.h"

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

class App
{
  private:
    int ups;
    int fps;

    bool          isDebug    = false;
    bool          isRunning  = false;
    SDL_Window   *gWindow    = nullptr;
    SDL_Renderer *gRenderer  = nullptr;
    std::vector<std::vector<GameObject>> gameObjects;

    const int SQUARE_WIDTH = 64;

    enum LogLevel
    {
        DEBUG,
        WARNING,
        ERROR,
        INFO
    };

    void log(std::string message, LogLevel logLevel);

  public:
    App(bool isDebug = false, int ups = 60, int fps = -1);
    int  run();
    bool init();
    void handleEvent(SDL_Event *event);
    void update();
    void render();
    void clean();
};