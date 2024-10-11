#include "Game.h"


Game::Game(int screenWidth, int screenHeight, Map *map, Player *player) : screenWidth(screenWidth), screenHeight(screenHeight), map(map), player(player) {
    this->screen = new wchar_t[screenWidth * screenHeight];
    this->screen[screenWidth * screenHeight - 1] = '\0';
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->graphics = std::make_unique<Graphics>(Graphics(screenWidth, screenHeight));
    this->camera = std::make_unique<Camera>(Camera(this));
    this->graphics->hijack();
}

void Game::update(float deltaTime) {
    this->camera->update(deltaTime);
    this->player->update(this, deltaTime);
    std::string deltaTimeRaw = std::to_string(deltaTime);
    for (int i = 0; i < deltaTimeRaw.size(); i++) {
        screen[i] = deltaTimeRaw[i];
    }
}

void Game::draw() {
    this->graphics->fill(screen, screenWidth * screenHeight, 0, 0);
}

void Game::stop() {
    this->graphics->stop();
}

void Game::updatePixel(int index, wchar_t character) {
    screen[index] = character;
}

wchar_t *Game::getScreen() const {
    return screen;
}

const Player *Game::getPlayer() {
    return this->player;
}

const std::vector<const Entity *> &Game::getEntities() {
    return this->entities;
}

Graphics *Game::getGraphics() {
    return this->graphics.get();
}

Map *Game::getMap() const {
    return map;
}

int Game::getScreenWidth() const {
    return screenWidth;
}

int Game::getScreenHeight() const {
    return screenHeight;
}
