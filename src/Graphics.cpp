#include "Graphics.h"

WORD rgbToConsoleColor(std::byte r, std::byte g, std::byte b) {
    WORD colorAttribute = 0;
    std::byte colorClamp{128};

    if (r > colorClamp)
        colorAttribute |= FOREGROUND_RED;
    if (g > colorClamp)
        colorAttribute |= FOREGROUND_GREEN;
    if (b > colorClamp)
        colorAttribute |= FOREGROUND_BLUE;
    if (r > colorClamp || g > colorClamp || b > colorClamp) {
        colorAttribute |= FOREGROUND_INTENSITY;
    }
    return colorAttribute;
}

Graphics::Graphics(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    this->length = screenWidth * screenHeight;
    this->renderRectangle = SMALL_RECT{0, 0, 1, 1};
}

void Graphics::hijack() {
    SetConsoleWindowInfo(consoleHandle, TRUE, &renderRectangle);
    SetConsoleScreenBufferSize(consoleHandle, {(short)screenWidth, (short) screenWidth});
    SetConsoleActiveScreenBuffer(consoleHandle);
    CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
    if (!GetConsoleScreenBufferInfo(consoleHandle, &screenBuffer))
        throw std::logic_error("GetConsoleScreenBufferInfo");
    if (screenHeight > screenBuffer.dwMaximumWindowSize.Y)
        throw std::logic_error("Screen Height / Font Height Too Big");
    if (screenWidth > screenBuffer.dwMaximumWindowSize.X)
        throw std::logic_error("Screen Width / Font Width Too Big");

    this->renderRectangle = {0, 0, (short) (screenWidth - 1), (short) (screenHeight - 1)};
    if (!SetConsoleWindowInfo(consoleHandle, TRUE, &renderRectangle))
        throw std::logic_error("SetConsoleWindowInfo");

    screen = new CHAR_INFO[screenWidth * screenHeight];
    memset(screen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);

    for (int i = 0; i < screenWidth * screenHeight; ++i) {
        screen[i].Attributes = FOREGROUND_INTENSITY;
    }
}

void Graphics::stop() {
    CloseHandle(consoleHandle);
}

void Graphics::update(int x, int y, std::byte red, std::byte green, std::byte blue) {
    screen[y * screenWidth + x].Attributes = rgbToConsoleColor(red, green, blue);
}

void Graphics::update(int x, int y, wchar_t new_character) {
    if (y < 0 || x < 0 || y > screenHeight || x > screenWidth)
        throw std::invalid_argument("x or y out of bounds: " + std::to_string(x) + " " + std::to_string(y));
    screen[y * screenWidth + x].Char.UnicodeChar = new_character;
}

void Graphics::fill(short x, short y) {
    if (!WriteConsoleOutputW(consoleHandle,
                        screen,
                        {(short) screenWidth, (short) screenHeight},
                        {x, y},
                        &renderRectangle))
        throw std::logic_error("WriteConsoleOutputW");
}
