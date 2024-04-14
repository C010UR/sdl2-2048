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

std::pair<int, int>
App::renderText(std::string msg, int x, int y, SDL_Color fg, SDL_Color bg, bool isSmall, bool isCentered)
{
    SDL_Surface *surface = TTF_RenderText_Shaded(isSmall ? this->smallFont : this->font, msg.c_str(), fg, bg);

    if (surface == nullptr) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return {-1, -1};
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->gRenderer, surface);

    if (texture == nullptr) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return {-1, -1};
    }

    int textW = 0;
    int textH = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
    SDL_Rect dstRect = {x, y, textW, textH};

    if (isCentered) {
        dstRect.x = x - textW / 2;
        dstRect.y = y - textH / 2;
    }

    if (SDL_RenderCopy(this->gRenderer, texture, nullptr, &dstRect) < 0) {
        logger->log("App::renderText", SDL_GetError(), Logger::LogLevel::ERROR);
        return {-1, -1};
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return {textW, textH};
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

    this->renderText(
        "2048.org",
        Config::padding,
        Config::padding,
        Config::fontColor,
        Config::backgroundColor,
        false,
        false);
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
    int scoreX1 = this->gridX + this->gridSize - Config::scoreWidth;
    int scoreX2 = scoreX1 + Config::scoreWidth;

    int scoreY1 = this->gridY - Config::padding - Config::scoreHeight;
    int scoreY2 = this->gridY - Config::padding;

    int bestX1 = scoreX1 - Config::padding - Config::scoreWidth;
    int bestX2 = bestX1 + Config::scoreWidth;

    this->renderRectangle(scoreX1, scoreY1, scoreX2, scoreY2, Config::gridBackgroundColor);
    this->renderRectangle(bestX1, scoreY1, bestX2, scoreY2, Config::gridBackgroundColor);

    int scoreTextX = scoreX1 + ((scoreX2 - scoreX1) / 2);
    int bestTextX  = bestX1 + ((bestX2 - bestX1) / 2);

    auto scoreSize = this->renderText(
        "SCORE",
        scoreTextX,
        scoreY1 + Config::padding,
        Config::gridForegroundColor,
        Config::gridBackgroundColor,
        true);

    this->renderText(
        "BEST",
        bestTextX,
        scoreY1 + Config::padding,
        Config::gridForegroundColor,
        Config::gridBackgroundColor,
        true);

    std::stringstream scoreStream;
    scoreStream << this->score;

    this->renderText(
        scoreStream.str(),
        scoreTextX,
        scoreY1 + scoreSize.second + Config::padding,
        Config::backgroundColor,
        Config::gridBackgroundColor,
        true);

    std::stringstream bestStream;
    bestStream << this->best;

    this->renderText(
        bestStream.str(),
        bestTextX,
        scoreY1 + scoreSize.second + Config::padding,
        Config::backgroundColor,
        Config::gridBackgroundColor,
        true);
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