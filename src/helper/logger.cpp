#include "helper/logger.h"

Logger::Logger(bool isDebug)
{
    this->isDebug = isDebug;
}

void Logger::log(std::string message, Logger::LogLevel logLevel)
{
    if (!this->isDebug && (logLevel == Logger::LogLevel::DEBUG || logLevel == Logger::LogLevel::WARNING)) {
        return;
    }

    int         colorCode = 0;
    std::string prefix    = "";

    switch (logLevel) {
        case Logger::LogLevel::WARNING:
            colorCode = 33;
            prefix    = "Warning: ";
            break;
        case Logger::LogLevel::ERROR:
            colorCode = 31;
            prefix    = "Error: ";
            break;
        case Logger::LogLevel::INFO:
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