#include "core/app.h"

int App::run()
{
    if (this->init() == false) {
        return -1;
    }

    SDL_Event event;

    double   msPerUpdate = 1000. / this->ups;
    double   msPerFrame  = 1000. / this->fps;
    unsigned start       = SDL_GetTicks();
    unsigned previous    = start;
    unsigned lag         = 0;
    unsigned elapsed     = 0;
    unsigned current     = 0;

    while (this->isRunning) {
        current = SDL_GetTicks();
        elapsed = current - previous;
        lag += elapsed;

        while (SDL_PollEvent(&event)) {
            this->handleEvent(&event);
        }

        while ((double)lag >= msPerUpdate) {
            this->update();
            lag -= msPerUpdate;
        }

        this->render();

        current = SDL_GetTicks();
        elapsed = current - previous;

        if (msPerFrame > elapsed) {
            SDL_Delay((int)(msPerFrame - elapsed));
        }
    }

    this->clean();

    return 0;
}