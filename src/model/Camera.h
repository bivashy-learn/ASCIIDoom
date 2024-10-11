#ifndef DOOMCONSOLE_CAMERA_H
#define DOOMCONSOLE_CAMERA_H
#include <cmath>
#include <vector>
class Game;

class Camera {
private:
    float fieldOfView = 3.14159f / 4.0f;
    float maxRenderDistance;
    Game* game;
public:
    explicit Camera(Game *game);

    void update(float deltaTime);
};


#endif //DOOMCONSOLE_CAMERA_H
