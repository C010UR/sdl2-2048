#pragma once

#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
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
    TTF_Font     *font      = nullptr;
    TTF_Font     *smallFont = nullptr;

    std::vector<std::vector<int>> blocks;

    int score = 0;
    int best = 0;

    Logger *logger = nullptr;

    int gridX    = 0;
    int gridY    = 0;
    int gridSize = 0;

    void renderRectangle(int x1, int y1, int x2, int y2, SDL_Color color);
    std::pair<int, int> renderText(std::string msg, int x, int y, SDL_Color fg, SDL_Color bg, bool isSmall = false, bool isCentered = true);
    void renderGrid();
    void renderScore();
    void renderBlocks();
    void renderBlock(int x, int y);

    int moveX = 0;
    int moveY = 0;

    void initBoard();
    void addBlock();
    int moveLeft();
    int moveRight();
    int moveUp();
    int moveDown();
    int moveHorizontal(int x, int y, int direction);
    int moveVertical(int x, int y, int direction);
    void addScore(int value);

  public:
    App(Logger *logger, int ups = 60, int fps = -1);
    int  run();
    bool init();
    void handleEvent(SDL_Event *event);
    void update();
    void render();
    void clean();
};