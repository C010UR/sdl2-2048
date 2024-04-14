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

void App::renderRectangle(int x1, int y1, int x2, int y2, SDL_Color color, int glowSize)
{
    // TODO: Figure out antialiasing
    if (x1 > x2) std::swap(x1, x2);
    if (y1 > y2) std::swap(y1, y2);

    if (glowSize > 0) {
        int stepReduction = Config::glowAlpha / glowSize;

        for (int i = 0; i < glowSize; i++) {
            int       expand = i;
            SDL_Color glowColor =
                {color.r, color.g, color.b, static_cast<Uint8>(std::max(0, Config::glowAlpha - stepReduction * i))};

            roundedBoxRGBA(
                this->gRenderer,
                x1 - expand,
                y1 - expand,
                x2 + expand,
                y2 + expand,
                Config::squareRadius + expand,
                glowColor.r,
                glowColor.g,
                glowColor.b,
                glowColor.a);
        }
    }

    roundedRectangleRGBA(this->gRenderer, x1, y1, x2, y2, Config::squareRadius, color.r, color.g, color.b, color.a);
    roundedBoxRGBA(this->gRenderer, x1, y1, x2, y2, Config::squareRadius, color.r, color.g, color.b, color.a);
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

    for (int x = 0; x < Config::squareNumber; x++) {
        for (int y = 0; y < Config::squareNumber; y++) {
            int cellX = this->gridX + (Config::padding * (x + 1)) + (Config::squareSize * x);
            int cellY = this->gridY + (Config::padding * (y + 1)) + (Config::squareSize * y);
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

    int power = this->blocks[y][x];

    Config::BlockData blockData =
        Config::blockData[(unsigned)power >= Config::blockData.size() ? Config::blockData.size() - 1 : power];

    this->renderRectangle(
        bgX,
        bgY,
        bgX + Config::squareSize,
        bgY + Config::squareSize,
        blockData.bgColor,
        blockData.glow);

    std::stringstream strStream;
    strStream << (unsigned)pow(2, power + 1);

    int fntX = bgX + Config::squareSize / 2;
    int fntY = bgY + Config::squareSize / 2;

    this->renderText(strStream.str(), fntX, fntY, blockData.fontColor, blockData.bgColor, blockData.isSmallFont);
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
        scoreY1 + Config::scoreTextVerticalOffset,
        Config::gridForegroundColor,
        Config::gridBackgroundColor,
        true);

    this->renderText(
        "BEST",
        bestTextX,
        scoreY1 + Config::scoreTextVerticalOffset,
        Config::gridForegroundColor,
        Config::gridBackgroundColor,
        true);

    std::stringstream scoreStream;
    scoreStream << this->score;

    this->renderText(
        scoreStream.str(),
        scoreTextX,
        scoreY1 + scoreSize.second + Config::scoreTextVerticalOffset,
        Config::backgroundColor,
        Config::gridBackgroundColor,
        true);

    std::stringstream bestStream;
    bestStream << this->best;

    this->renderText(
        bestStream.str(),
        bestTextX,
        scoreY1 + scoreSize.second + Config::scoreTextVerticalOffset,
        Config::backgroundColor,
        Config::gridBackgroundColor,
        true);
}

void App::renderBlocks()
{
    for (int y = 0; y < Config::squareNumber; y++) {
        for (int x = 0; x < Config::squareNumber; x++) {
            if (this->blocks[y][x] >= 0) {
                this->renderBlock(x, y);
            };
        }
    }
}