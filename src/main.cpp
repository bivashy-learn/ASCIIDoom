#include <iostream>
#include <chrono>
#include "Game.h"

int main() {
    int width = 320, height = 240;
    int mapWidth = 16, mapHeight = 16;
    std::wstring rawMap;
    rawMap += L"XXXXXXXXXXXXXXXX";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X.....X........X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X........X.....X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"X..............X";
    rawMap += L"XXXXXXXXXXXXXXXX";

    Player player(8.0, 4.0, 0.0);
    Map map(rawMap, mapWidth, mapHeight);

    Game game(width, height, &map, &player);

    std::chrono::time_point<std::chrono::system_clock> previousTime = std::chrono::system_clock::now();
    while (true) {
        std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float> deltaTimeDuration = currentTime - previousTime;
        previousTime = currentTime;
        float deltaTimeMillis = deltaTimeDuration.count();

        game.update(deltaTimeMillis);
        game.draw();
    }
    game.stop();
    return 0;
}
