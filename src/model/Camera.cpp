#include "Camera.h"
#include "../Game.h"

Camera::Camera(Game *game) : game(game) {
    maxRenderDistance = std::sqrt(std::pow(game->getMap()->getWidth(), 2.0f) + std::pow(game->getMap()->getHeight(), 2.0f));
    wallShades.push_back(0x2591);
    wallShades.push_back(0x2592);
    wallShades.push_back(0x2593);
    wallShades.push_back(0x2588);
    floorShades.push_back('#');
}

void Camera::update(float deltaTime) {
    int screenWidth = game->getScreenWidth();
    int screenHeight = game->getScreenHeight();
    const Player *player = game->getPlayer();
    Map *map = game->getMap();
    for (int x = 0; x < screenWidth; ++x) {
        float halfFieldOfView = fieldOfView / 2.0f;
        float rayAngle = (player->getDirectionAngle() - halfFieldOfView) + ((float) x / (float) screenWidth) * fieldOfView;
        float distanceToWall = 0;
        bool wallFound = false;

        float eyeDirectionX = sinf(rayAngle);
        float eyeDirectionY = cosf(rayAngle);

        while (!wallFound) {
            distanceToWall += 0.1f;

            int futureX = (int)(player->getX() + eyeDirectionX * distanceToWall);
            int futureY = (int)(player->getY() + eyeDirectionY * distanceToWall);

            if (futureX < 0 || futureX >= map->getWidth() || futureY < 0 || futureY >= map->getHeight()) {
                wallFound = true;
                distanceToWall = maxRenderDistance;
            } else if (map->getRawMap()[futureX * map->getWidth() + futureY] == 'X') {
                wallFound = true;
            }
        }
        if (distanceToWall < 0.1f) distanceToWall = 0.1f;
        int ceilingDistance = (int)((float)screenHeight / 2.0f - (float)screenHeight / distanceToWall);
        ceilingDistance = std::max(0, ceilingDistance);
        int floorDistance = screenHeight - ceilingDistance;
        floorDistance = std::min(screenHeight, floorDistance);

        short shade = ' ';
        int currentShadeIndex = 0;
        for (const auto &currentShade: wallShades) {
            if ((float)ceilingDistance <= maxRenderDistance / (float)currentShadeIndex)
                shade = currentShade;
            currentShadeIndex++;
        }

        for (int y = 0; y < screenHeight; ++y) {
            int index = y * screenWidth + x;
            if (y < ceilingDistance)
                game->updatePixel(index, L' ');
            else if (y >= ceilingDistance && y <= floorDistance)
                game->updatePixel(index, shade);
            else {
                game->updatePixel(index, L' ');
            }
        }
    }

}


