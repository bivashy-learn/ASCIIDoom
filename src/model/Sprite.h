#ifndef DOOMCONSOLE_SPRITE_H
#define DOOMCONSOLE_SPRITE_H

#include <vector>
#include <string>
#include "../../third_party/lodepng/lodepng.h"
#include <iostream>

struct SimpleColor {
    int red, green, blue;
};

class Sprite {
private:
    unsigned width, height;
    std::vector<unsigned char> rawImage;
public:
    Sprite(const std::string &file);

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    const std::vector<unsigned char> &getRawImage() const;

    wchar_t getSampleGlyph(float x, float y);

    SimpleColor getSampleColor(float x, float y);
};


#endif //DOOMCONSOLE_SPRITE_H
