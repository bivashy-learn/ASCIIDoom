#include "Map.h"

#include <utility>

Map::Map(std::wstring rawMap, int width, int height) : rawMap(std::move(rawMap)), width(width), height(height) {
}

const std::wstring &Map::getRawMap() const {
    return rawMap;
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

int Map::getSize() const {
    return width * height;
}
