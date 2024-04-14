#include "core/app.h"
#include "core/config.h"

#include <iterator>
#include <utility>

void App::update()
{
    int movementCount = 0;

    if (this->moveX == -1) {
        movementCount = this->moveLeft();
    } else if (this->moveX == 1) {
        movementCount = this->moveRight();
    } else if (this->moveY == -1) {
        movementCount = this->moveDown();
    } else if (this->moveY == 1) {
        movementCount = this->moveUp();
    }

    this->moveX = 0;
    this->moveY = 0;

    if (movementCount > 0) {
        this->logger->log("App::update", "Creating a block", Logger::LogLevel::INFO);
        this->addBlock();
    }
}

void App::addBlock()
{
    std::vector<std::pair<int, int>> emptySpaces;

    for (int y = 0; y < Config::squareNumber; y++) {
        for (int x = 0; x < Config::squareNumber; x++) {
            if (this->blocks[y][x] < 0) {
                emptySpaces.push_back({x, y});
            }
        }
    }

    std::pair<int, int> target = emptySpaces[rand() % emptySpaces.size()];

    this->blocks[target.second][target.first] = rand() % 2;
}

int App::moveHorizontal(int x, int y, int direction)
{
    int movementCount = 0;

    while (x + direction >= 0 && x + direction < Config::squareNumber) {
        int currentBlock = this->blocks[y][x];
        int nextBlock    = this->blocks[y][x + direction];

        if (nextBlock < 0) {
            this->blocks[y][x + direction] = currentBlock;
            this->blocks[y][x]             = -1;
        } else if (nextBlock == currentBlock) {
            this->blocks[y][x + direction]++;
            this->blocks[y][x] = -1;

            this->addScore(this->blocks[y][x + direction] + 1);

            return movementCount;
        } else {
            return movementCount;
        }

        movementCount++;
        this->logger->logMovement(x, y, x + direction, y);

        x += direction;
    }

    return movementCount;
}

int App::moveVertical(int x, int y, int direction)
{
    int movementCount = 0;

    while (y + direction >= 0 && y + direction < Config::squareNumber) {
        int currentBlock = this->blocks[y][x];
        int nextBlock    = this->blocks[y + direction][x];

        if (nextBlock < 0) {
            this->blocks[y + direction][x] = currentBlock;
            this->blocks[y][x]             = -1;
        } else if (nextBlock == currentBlock) {
            this->blocks[y + direction][x]++;
            this->blocks[y][x] = -1;

            this->addScore(this->blocks[y + direction][x]);

            return movementCount;
        } else {
            return movementCount;
        }

        movementCount++;
        this->logger->logMovement(x, y, x, y + direction);

        y += direction;
    }

    return movementCount;
}

int App::moveLeft()
{
    int movementCount = 0;

    for (int x = 0; x < Config::squareNumber; x++) {
        for (int y = 0; y < Config::squareNumber; y++) {
            if (this->blocks[y][x] >= 0) {
                movementCount += this->moveHorizontal(x, y, -1);
            }
        }
    }

    return movementCount;
}

int App::moveRight()
{
    int movementCount = 0;

    for (int x = Config::squareNumber - 1; x >= 0; x--) {
        for (int y = 0; y < Config::squareNumber; y++) {
            if (this->blocks[y][x] >= 0) {
                movementCount += this->moveHorizontal(x, y, 1);
            }
        }
    }

    return movementCount;
}

int App::moveUp()
{
    int movementCount = 0;

    for (int y = 0; y < Config::squareNumber; y++) {
        for (int x = 0; x < Config::squareNumber; x++) {
            if (this->blocks[y][x] >= 0) {
                movementCount += this->moveVertical(x, y, -1);
            }
        }
    }

    return movementCount;
}

int App::moveDown()
{
    int movementCount = 0;

    for (int y = Config::squareNumber - 1; y >= 0; y--) {
        for (int x = 0; x < Config::squareNumber; x++) {
            if (this->blocks[y][x] >= 0) {
                movementCount += this->moveVertical(x, y, 1);
            }
        }
    }

    return movementCount;
}

void App::addScore(int value)
{
    this->score += pow(2, value + 1);

    if (this->score > this->best) {
        this->best = this->score;
    }
}