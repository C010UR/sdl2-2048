#include "SDL_render.h"
#include "core/app.h"
#include "core/config.h"
#include "helper/canvas.h"

void App::render()
{
    this->logger->log("Render call", Logger::LogLevel::INFO);

    if (SDL_RenderClear(this->gRenderer) < 0) {
        this->logger->log(SDL_GetError(), Logger::LogLevel::ERROR);
        return;
    }

    int bgSize = Config::padding * 5 + Config::squareSize * 4;
    int bgX    = (Config::screenWidth - bgSize) / 2;
    int bgY    = Config::screenHeight - bgSize - Config::padding;

    Canvas::drawRectangle(this->gRenderer, bgX, bgY, bgX + bgSize, bgY + bgSize, Config::gridBackgroundColor);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int bgX2 = bgX + (Config::padding * (i + 1)) + (Config::squareSize * i);
            int bgY2 = bgY + (Config::padding * (j + 1)) + (Config::squareSize * j);
            Canvas::drawRectangle(this->gRenderer, bgX2, bgY2, bgX2 + Config::squareSize, bgY2 + Config::squareSize, Config::gridForegroundColor);
        }
    }

    // TODO: draw text
    // TODO: create square object

    // std::string msg = "hello";
    // SDL_Rect rect = {10, 10, 100, 32};

    // Canvas::drawText(this->gRenderer, &msg, &rect, Config::fontColor);

    // for (unsigned layer = 0; layer < this->gameObjects.size(); layer++) {
    //     for (unsigned i = 0; i < this->gameObjects[layer].size(); i++) {
    //         this->gameObjects[layer][i].render();
    //     }
    // }


    SDL_SetRenderDrawColor(
        this->gRenderer,
        Config::backgroundColor.r,
        Config::backgroundColor.g,
        Config::backgroundColor.b,
        Config::backgroundColor.a);

    SDL_RenderPresent(this->gRenderer);
}