#include "app.h"

#include <chrono>
#include <ctime>

App::App(bool isDebug, int ups, int fps)
{
    this->isDebug   = isDebug;
    this->isRunning = true;
    this->ups       = ups;
    this->fps       = fps;
}

void App::log(std::string message, App::LogLevel logLevel)
{
    if (!this->isDebug && (logLevel == App::LogLevel::DEBUG || logLevel == App::LogLevel::WARNING)) {
        return;
    }

    int         colorCode = 0;
    std::string prefix    = "";

    switch (logLevel) {
        case App::LogLevel::WARNING:
            colorCode = 33;
            prefix    = "Warning: ";
            break;
        case App::LogLevel::ERROR:
            colorCode = 31;
            prefix    = "Error: ";
            break;
        case App::LogLevel::INFO:
            colorCode = 36;
            break;
        default:
            colorCode = 0;
            break;
    }

    std::time_t t   = std::time(0);
    std::tm    *now = std::localtime(&t);

    std::cout << "\033[" << colorCode << "m[" << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-"
              << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "]\033[0m "
              << prefix << message << std::endl;
}