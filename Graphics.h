#ifndef DOOMCONSOLE_GRAPHICS_H
#define DOOMCONSOLE_GRAPHICS_H
#include <windows.h>
#include <iostream>

class Graphics {
private:
    HANDLE consoleHandle;
    int screenWidth, screenHeight;
    DWORD bytesWritten = 0;
public:
    Graphics(int screenWidth, int screenHeight);

    void hijack();

    void stop();

    void fill(const wchar_t *rawMap, int length, short x, short y);

    HANDLE getConsoleHandle();
};


#endif //DOOMCONSOLE_GRAPHICS_H
