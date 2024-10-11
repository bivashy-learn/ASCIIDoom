#ifndef DOOMCONSOLE_ENTITY_H
#define DOOMCONSOLE_ENTITY_H

class Game;

class Entity {
protected:
    float x{}, y{};
public:
    virtual void update(Game *game, float deltaTime) = 0;

    virtual float getX() const {
        return x;
    }

    virtual float getY() const {
        return y;
    }
};


#endif //DOOMCONSOLE_ENTITY_H
