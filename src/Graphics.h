#ifndef DOOMCONSOLE_GRAPHICS_H
#define DOOMCONSOLE_GRAPHICS_H
#include <windows.h>
#include <iostream>

class Graphics {
private:
    HANDLE consoleHandle;
    int screenWidth, screenHeight, length;
    DWORD bytesWritten = 0;
    wchar_t *screen;
public:
    Graphics(int screenWidth, int screenHeight);

    virtual ~Graphics();

    void hijack();

    void stop();

    void update(int x, int y, wchar_t new_character);

    void fill(short x, short y);
};


#endif //DOOMCONSOLE_GRAPHICS_H
