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

    bool hasEmpty = false;

    for (int x = 0; x < Config::squareNumber; x++) {
        for (int y = 0; y < Config::squareNumber; y++) {
            if (this->blocks[x][y] < 0) {
                hasEmpty = true;
                break;
            }
        }

        if (hasEmpty) {
            break;
        }
    }

    if (!hasEmpty) {
        this->isRunning = false;
    }

    if (movementCount > 0) {
        this->logger->log("App::update", "Creating a block", Logger::LogLevel::INFO);
        this->addBlock();
    }

    this->moveX = 0;
    this->moveY = 0;
}

void App::addBlock()
{
    std::vector<std::pair<int, int>> emptySpaces;

    for (int x = 0; x < Config::squareNumber; x++) {
        for (int y = 0; y < Config::squareNumber; y++) {
            if (this->blocks[x][y] < 0) {
                emptySpaces.push_back({x, y});
            }
        }
    }

    std::pair<int, int> target = emptySpaces[rand() % emptySpaces.size()];

    this->blocks[target.first][target.second] = rand() % 2;
}

int App::moveHorizontal(int x, int y, int direction)
{
    int movementCount = 0;

    while (x + direction >= 0 && x + direction < Config::squareNumber) {
        int currentBlock = this->blocks[x][y];
        int nextBlock    = this->blocks[x + direction][y];

        if (nextBlock < 0) {
            this->blocks[x + direction][y] = currentBlock;
            this->blocks[x][y]             = -1;
        } else if (nextBlock == currentBlock) {
            this->blocks[x + direction][y]++;
            this->blocks[x][y] = -1;

            this->score += pow(2, this->blocks[x + direction][y] + 1);

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
        int currentBlock = this->blocks[x][y];
        int nextBlock    = this->blocks[x][y + direction];

        if (nextBlock < 0) {
            this->blocks[x][y + direction] = currentBlock;
            this->blocks[x][y]             = -1;
        } else if (nextBlock == currentBlock) {
            this->blocks[x][y + direction]++;
            this->blocks[x][y] = -1;

            this->score += pow(2, this->blocks[x][y + direction] + 1);

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

    for (int y = 0; y < Config::squareNumber; y++) {
        for (int x = 0; x < Config::squareNumber; x++) {
            if (this->blocks[x][y] >= 0) {
                movementCount += this->moveHorizontal(x, y, -1);
            }
        }
    }

    return movementCount;
}

int App::moveRight()
{
    int movementCount = 0;

    for (int y = 0; y < Config::squareNumber; y++) {
        for (int x = Config::squareNumber - 1; x >= 0; x--) {
            if (this->blocks[x][y] >= 0) {
                movementCount += this->moveHorizontal(x, y, 1);
            }
        }
    }

    return movementCount;
}

int App::moveUp()
{
    int movementCount = 0;

    for (int x = 0; x < Config::squareNumber; x++) {
        for (int y = 0; y < Config::squareNumber; y++) {
            if (this->blocks[x][y] >= 0) {
                movementCount += this->moveVertical(x, y, -1);
            }
        }
    }

    return movementCount;
}

int App::moveDown()
{
    int movementCount = 0;

    for (int x = 0; x < Config::squareNumber; x++) {
        for (int y = Config::squareNumber - 1; y >= 0; y--) {
            if (this->blocks[x][y] >= 0) {
                movementCount += this->moveVertical(x, y, 1);
            }
        }
    }

    return movementCount;
}