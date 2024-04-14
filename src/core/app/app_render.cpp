#include "SDL2_gfxPrimitives.h"
#include "core/app.h"
#include "core/config.h"

#include <sstream>

void App::render()
{
    if (SDL_RenderClear(this->gRenderer) < 0) {
        this->logger->log("App::render", SDL_GetError(), Logger::LogLevel::ERROR);
        return;
    }

    this->renderGrid();
    this->renderScore();
    this->renderBlocks();

    SDL_SetRenderDrawColor(
        this->gRenderer,
        Config::backgroundColor.r,
        Config::backgroundColor.g,
        Config::backgroundColor.b,
        Config::backgroundColor.a);

    SDL_RenderPresent(this->gRenderer);
}

void App::renderRectangle(int x1, int y1, int x2, int y2, SDL_Color color)
{
    int result =
        roundedBoxRGBA(this->gRenderer, x1, y1, x2, y2, Config::squareRounding, color.r, color.g, color.b, color.a);

    if (result < 0) {
        this->logger->log("Canvas::drawRectangle", SDL_GetError(), Logger::LogLevel::ERROR);
    }
}

void App::renderText(std::string msg, int x, int y, SDL_Color fg, SDL_Color bg, bool isSmall)
{
    SDL_Surface *surface = TTF_RenderText_Shaded(isSmall ? this->smallFont : this->font, msg.c_str(), fg, bg);

    if (surface == nullptr) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->gRenderer, surface);

    if (texture == nullptr) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return;
    }

    int textW = 0;
    int textH = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
    SDL_Rect dstRect = {x - textW / 2, y - textH / 2, textW, textH};

    if (SDL_RenderCopy(this->gRenderer, texture, nullptr, &dstRect) < 0) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return;
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void App::renderGrid()
{
    this->renderRectangle(
        this->gridX,
        this->gridY,
        this->gridX + this->gridSize,
        this->gridY + this->gridSize,
        Config::gridBackgroundColor);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int cellX = this->gridX + (Config::padding * (i + 1)) + (Config::squareSize * i);
            int cellY = this->gridY + (Config::padding * (j + 1)) + (Config::squareSize * j);
            this->renderRectangle(
                cellX,
                cellY,
                cellX + Config::squareSize,
                cellY + Config::squareSize,
                Config::gridForegroundColor);
        }
    }

    this->renderText("2048.org", this->gridX + 72, this->gridY - 72, Config::fontColor, Config::backgroundColor);
}

void App::renderBlock(int x, int y)
{
    int bgX = this->gridX + (Config::padding * (x + 1)) + (Config::squareSize * x);
    int bgY = this->gridY + (Config::padding * (y + 1)) + (Config::squareSize * y);

    int power = this->blocks[x][y];

    int color = (unsigned)power >= Config::powerColors.size() ? Config::powerColors.size() - 1 : power;

    this->renderRectangle(bgX, bgY, bgX + Config::squareSize, bgY + Config::squareSize, Config::powerColors[color]);

    std::stringstream strStream;
    strStream << (unsigned)pow(2, power + 1);

    int fntX = bgX + Config::squareSize / 2;
    int fntY = bgY + Config::squareSize / 2;

    this->renderText(strStream.str(), fntX, fntY, Config::fontPowerColors[color], Config::powerColors[color]);
}

void App::renderScore()
{
    int x1 = this->gridX + this->gridSize - 128;
    int y1 = this->gridY - 96;
    int x2 = this->gridX + this->gridSize;
    int y2 = this->gridY - 40;

    this->renderRectangle(x1, y1, x2, y2, Config::gridBackgroundColor);

    int textX = x1 + ((x2 - x1) / 2);

    this->renderText("SCORE", textX, y1 + 16, Config::gridForegroundColor, Config::gridBackgroundColor, true);

    std::stringstream strStream;
    strStream << this->score;

    this->renderText(strStream.str(), textX, y1 + 36, Config::backgroundColor, Config::gridBackgroundColor, true);
}

void App::renderBlocks()
{
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (this->blocks[x][y] >= 0) {
                this->renderBlock(x, y);
            };
        }
    }
}