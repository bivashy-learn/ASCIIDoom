#include "Player.h"
#include "../Game.h"

Player::Player(float x, float y, float directionAngle) : directionAngle(directionAngle) {
    this->x = x;
    this->y = y;
}

void Player::update(Game *game, float deltaTime) {
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        directionAngle -= rotationSensitivity * deltaTime;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        directionAngle += rotationSensitivity * deltaTime;
    }
    if (GetAsyncKeyState('W') & 0x8000) {
        float deltaX = sinf(directionAngle) * movementSpeed * deltaTime;
        float deltaY = cosf(directionAngle) * movementSpeed * deltaTime;
        move(game, deltaX, deltaY);
    }
    if (GetAsyncKeyState('A') & 0x8000) {
        float deltaX = -cosf(directionAngle) * strafeSpeed * deltaTime;
        float deltaY = sinf(directionAngle) * strafeSpeed * deltaTime;
        move(game, deltaX, deltaY);
    }
    if (GetAsyncKeyState('S') & 0x8000) {
        float deltaX = -sinf(directionAngle) * movementSpeed * deltaTime;
        float deltaY = -cosf(directionAngle) * movementSpeed * deltaTime;
        move(game, deltaX, deltaY);
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        float deltaX = cosf(directionAngle) * strafeSpeed * deltaTime;
        float deltaY = -sinf(directionAngle) * strafeSpeed * deltaTime;
        move(game, deltaX, deltaY);
    }
}

void Player::move(Game *game, float deltaX, float deltaY) {
    int futureX = (int) (x + deltaX);
    int futureY = (int) (y + deltaY);
    Map *map = game->getMap();
    char futureTile = map->getRawMap()[futureX * map->getWidth() + futureY];
    if (futureTile != 'X') {
        x += deltaX;
        y += deltaY;
    }
}

float Player::getDirectionAngle() const {
    return directionAngle;
}
