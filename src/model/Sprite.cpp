#include "Sprite.h"

#define SOLID_PIXEL 0x2588

Sprite::Sprite(const std::string &file) {
    unsigned error = lodepng::decode(rawImage, width, height, file);
    if (error)
        throw std::logic_error("Cannot decode image");
}

unsigned int Sprite::getWidth() const {
    return width;
}

unsigned int Sprite::getHeight() const {
    return height;
}

const std::vector<unsigned char> &Sprite::getRawImage() const {
    return rawImage;
}

wchar_t Sprite::getSampleGlyph(float x, float y) {
    int colorBitSize = 4;
    int relativeX = (int) (x * (float) width);
    int relativeY = (int) (y * (float) height - 1.0f);
    if (relativeX < 0 || relativeX >= width || relativeY < 0 || relativeY >= height)
        return L' ';
    unsigned int alpha = rawImage[colorBitSize * relativeY * width + colorBitSize * relativeX + 3];
    if (alpha < 128)
        return L' ';
    return SOLID_PIXEL;
}

SimpleColor Sprite::getSampleColor(float x, float y) {
    unsigned int colorBitSize = 4;
    int relativeX = (int) (x * (float) width);
    int relativeY = (int) (y * (float) height - 1.0f);
    if (relativeX < 0 || relativeX >= width || relativeY < 0 || relativeY >= height)
        return {0, 0, 0};
    int red = rawImage[colorBitSize * relativeY * width + colorBitSize * relativeX + 0];
    int green = rawImage[colorBitSize * relativeY * width + colorBitSize * relativeX + 1];
    int blue = rawImage[colorBitSize * relativeY * width + colorBitSize * relativeX + 2];
    return {red, green, blue};
}

