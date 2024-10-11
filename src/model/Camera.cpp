#include <algorithm>
#include "Camera.h"
#include "../Game.h"

Camera::Camera(Game *game) : game(game) {
    maxRenderDistance = std::sqrt(
            std::pow(game->getMap()->getWidth(), 2.0f) + std::pow(game->getMap()->getHeight(), 2.0f));
    wallShades.push_back(0x2591);
    wallShades.push_back(0x2592);
    wallShades.push_back(0x2593);
    wallShades.push_back(0x2588);
}

void Camera::update(float deltaTime) {
    int screenWidth = game->getScreenWidth();
    int screenHeight = game->getScreenHeight();
    const Player *player = game->getPlayer();
    Map *map = game->getMap();
    Graphics *graphics = game->getGraphics();
    for (int x = 0; x < screenWidth; ++x) {
        float halfFieldOfView = fieldOfView / 2.0f;
        float rayAngle =
                (player->getDirectionAngle() - halfFieldOfView) + ((float) x / (float) screenWidth) * fieldOfView;
        float distanceToWall = 0;
        bool wallFound = false;
        bool boundary = false;

        float eyeDirectionX = sinf(rayAngle);
        float eyeDirectionY = cosf(rayAngle);

        while (!wallFound) {
            distanceToWall += 0.01f;

            int futureX = (int) (player->getX() + eyeDirectionX * distanceToWall);
            int futureY = (int) (player->getY() + eyeDirectionY * distanceToWall);

            if (futureX < 0 || futureX >= map->getWidth() || futureY < 0 || futureY >= map->getHeight()) {
                wallFound = true;
                distanceToWall = maxRenderDistance;
            } else if (map->getRawMap()[futureX * map->getWidth() + futureY] == 'X') {
                wallFound = true;
                // To highlight tile boundaries, cast a ray from each corner
                // of the tile, to the player. The more coincident this ray
                // is to the rendering ray, the closer we are to a tile
                // boundary, which we'll shade to add detail to the walls
                std::vector<std::pair<float, float>> p;

                // Test each corner of hit tile, storing the distance from
                // the player, and the calculated dot product of the two rays
                for (int tx = 0; tx < 2; tx++)
                    for (int ty = 0; ty < 2; ty++) {
                        // Angle of corner to eye
                        float vy = (float) futureY + (float) ty - player->getY();
                        float vx = (float) futureX + (float) tx - player->getX();
                        float d = std::sqrt(vx * vx + vy * vy);
                        float dot = (eyeDirectionX * vx / d) + (eyeDirectionY * vy / d);
                        p
                                .push_back(
                                        std::make_pair(d, dot)
                                );
                    }

                // Sort Pairs from closest to farthest
                std::sort(p.begin(), p.end(),
                          [](const std::pair<float, float> &left, const std::pair<float, float> &right) {
                              return left.first < right.first;
                          });

                // First two/three are closest (we will never see all four)
                float fBound = 0.01;
                if (acos(p.at(0).second) < fBound) boundary = true;
                if (acos(p.at(1).second) < fBound) boundary = true;
                if (acos(p.at(2).second) < fBound) boundary = true;
            }
        }
        if (distanceToWall < 0.1f) distanceToWall = 0.1f;
        int ceilingDistance = (int) ((float) screenHeight / 2.0f - (float) screenHeight / distanceToWall);
        ceilingDistance = std::max(0, ceilingDistance);
        int floorDistance = screenHeight - ceilingDistance;
        floorDistance = std::min(screenHeight, floorDistance);

        short shade = ' ';
        int currentShadeIndex = 0;
        for (const auto &currentShade: wallShades) {
            if ((float) ceilingDistance <= maxRenderDistance / (float) currentShadeIndex)
                shade = currentShade;
            currentShadeIndex++;
        }
        if (boundary) shade = ' ';

        for (int y = 0; y < screenHeight; ++y) {
            if (y < ceilingDistance)
                graphics->update(x, y, L' ');
            else if (y >= ceilingDistance && y <= floorDistance)
                graphics->update(x, y, shade);
            else {
                wchar_t floorShade;
                float distanceToFloor = 1.0f - (((float) y - screenHeight / 2.0f) / ((float) screenWidth / 2.0f));
                if (distanceToFloor < 0.25) floorShade = '#';
                else if (distanceToFloor < 0.5) floorShade = 'x';
                else if (distanceToFloor < 0.75) floorShade = '#';
                else if (distanceToFloor < 0.9) floorShade = 'x';
                else floorShade = '.';
                graphics->update(x, y, floorShade);
            }
        }
    }

}


