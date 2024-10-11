#include <algorithm>
#include "Camera.h"
#include "../Game.h"
#include "Sprite.h"

#define M_PI_3_4 2.35619449019f

Sprite brickSprite("../resources/brick.png");

Camera::Camera(Game *game) : game(game) {
    maxRenderDistance = std::sqrt(
            std::pow(game->getMap()->getWidth(), 2.0f) + std::pow(game->getMap()->getHeight(), 2.0f));
}

void Camera::update(float deltaTime) {
    int screenWidth = game->getScreenWidth();
    int screenHeight = game->getScreenHeight();
    const Player *player = game->getPlayer();
    Map *map = game->getMap();
    std::wstring rawMap = map->getRawMap();
    Graphics *graphics = game->getGraphics();
    for (int x = 0; x < screenWidth; ++x) {
        float halfFieldOfView = fieldOfView / 2.0f;
        float rayAngle =
                (player->getDirectionAngle() - halfFieldOfView) + ((float) x / (float) screenWidth) * fieldOfView;
        float distanceToWall = 0;
        bool wallFound = false;

        float eyeDirectionX = sinf(rayAngle);
        float eyeDirectionY = cosf(rayAngle);

        float sampleX = 0.0f;

        while (!wallFound) {
            distanceToWall += 0.01f;

            int futureX = (int) (player->getX() + eyeDirectionX * distanceToWall);
            int futureY = (int) (player->getY() + eyeDirectionY * distanceToWall);

            if (futureX < 0 || futureX >= map->getWidth() || futureY < 0 || futureY >= map->getHeight()) {
                wallFound = true;
                distanceToWall = maxRenderDistance;
            } else if (rawMap[futureX * map->getWidth() + futureY] == 'X') {
                wallFound = true;

                float blockMiddleX = (float) futureX + 0.5f;
                float blockMiddleY = (float) futureY + 0.5f;

                float futureRayY = player->getY() + eyeDirectionY * distanceToWall;
                float futureRayX = player->getX() + eyeDirectionX * distanceToWall;

                float wallRayAngle = atan2f((futureRayY - blockMiddleY), (futureRayX - blockMiddleX));

                if (wallRayAngle >= -M_PI_4 && wallRayAngle < M_PI_4)
                    sampleX = futureRayY - (float) futureY;
                if (wallRayAngle >= M_PI_4 && wallRayAngle < M_PI_3_4)
                    sampleX = futureRayX - (float) futureX;
                if (wallRayAngle < -M_PI_4 && wallRayAngle >= -M_PI_3_4)
                    sampleX = futureRayX - (float) futureX;
                if (wallRayAngle >= M_PI_3_4 || wallRayAngle < -M_PI_3_4)
                    sampleX = futureRayY - (float) futureY;
            }
        }
        if (distanceToWall < 0.1f) distanceToWall = 0.1f;
        int ceilingDistance = (int) ((float) screenHeight / 2.0f - (float) screenHeight / distanceToWall);
        ceilingDistance = std::max(0, ceilingDistance);
        int floorDistance = screenHeight - ceilingDistance;
        floorDistance = std::min(screenHeight, floorDistance);

        for (int y = 0; y < screenHeight; ++y) {
            if (y < ceilingDistance) {
                graphics->update(x, y, L' ');
            } else if (y >= ceilingDistance && y <= floorDistance) {
                float sampleY =
                        ((float) y - (float) ceilingDistance) / ((float) floorDistance - (float) ceilingDistance);

                wchar_t glyph = brickSprite.getSampleGlyph(sampleX, sampleY);
                SimpleColor color = brickSprite.getSampleColor(sampleX, sampleY);
                graphics->update(x, y, glyph, color.red, color.green, color.blue);
            } else {
                graphics->update(x, y, L' ', 0, 255, 0, true);
            }
        }
    }

}


