#ifndef DOOMCONSOLE_PLAYER_H
#define DOOMCONSOLE_PLAYER_H


#include "Entity.h"
#include <windows.h>
#include <cmath>

const float movementSpeed = 0.8f;
const float strafeSpeed = 2.0f;
const float rotationSensitivity = 0.8f;

class Game;

class Player : public Entity {
private:
    float directionAngle;

    void move(Game *game, float deltaX, float deltaY);
public:
    Player(float x, float y, float directionAngle);

    float getDirectionAngle() const;

    void update(Game *game, float deltaTime) override;
};


#endif //DOOMCONSOLE_PLAYER_H
