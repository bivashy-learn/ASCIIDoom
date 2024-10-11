#ifndef DOOMCONSOLE_MAP_H
#define DOOMCONSOLE_MAP_H

#include <iostream>

class Map {
private:
    std::wstring rawMap;
    int width, height;
public:
    Map(std::wstring rawMap, int width, int height);

    const std::wstring &getRawMap() const;

    int getWidth() const;

    int getHeight() const;

    int getSize() const;
};


#endif //DOOMCONSOLE_MAP_H
