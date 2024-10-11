#ifndef DOOMCONSOLE_GRAPHICS_H
#define DOOMCONSOLE_GRAPHICS_H
#include <windows.h>
#include <iostream>

class Graphics {
private:
    HANDLE consoleHandle;
    int screenWidth, screenHeight, length;
    SMALL_RECT renderRectangle;
    CHAR_INFO *screen;
public:
    Graphics(int screenWidth, int screenHeight);

    void hijack();

    void stop();

    void update(int x, int y, wchar_t new_character, int red = 0, int green = 0, int blue = 0, bool background = false);

    void fill(short x, short y);
};


#endif //DOOMCONSOLE_GRAPHICS_H
