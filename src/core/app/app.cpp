#include "core/app.h"

App::App(Logger *logger, int ups, int fps)
{
    this->logger    = logger;
    this->isRunning = true;
    this->ups       = ups;
    this->fps       = fps;
}