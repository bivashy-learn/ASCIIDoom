#ifndef DOOMCONSOLE_GAME_H
#define DOOMCONSOLE_GAME_H

#include <iostream>
#include <memory>
#include <vector>
#include "Graphics.h"
#include "model/Map.h"
#include "model/Entity.h"
#include "model/Camera.h"
#include "model/Player.h"

class Game {
private:
    int screenWidth, screenHeight;
    wchar_t *screen;
    Map* map;
    Player* player;
    std::vector<const Entity *> entities;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Graphics> graphics;
public:
    Game(int screenWidth, int screenHeight, Map* map, Player *player);

    void update(float deltaTime);

    void draw();

    void stop();

    void updatePixel(int index, wchar_t character);

    wchar_t *getScreen() const;

    const Player *getPlayer();

    const std::vector<const Entity*> &getEntities();

    Graphics *getGraphics();

    Map *getMap() const;

    int getScreenWidth() const;

    int getScreenHeight() const;
};


#endif //DOOMCONSOLE_GAME_H
