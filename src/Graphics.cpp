#include "Graphics.h"

WORD rgbToConsoleColor(int r, int g, int b, bool background) {
    WORD colorAttribute = 0;
    int colorClamp{128};

    if (r > colorClamp)
        colorAttribute |= background ? BACKGROUND_RED : FOREGROUND_RED;
    if (g > colorClamp)
        colorAttribute |= background ? BACKGROUND_GREEN : FOREGROUND_GREEN;
    if (b > colorClamp)
        colorAttribute |= background ? BACKGROUND_BLUE : FOREGROUND_GREEN;
    colorAttribute |= background ? BACKGROUND_INTENSITY : FOREGROUND_INTENSITY;
    return colorAttribute;
}


WORD precomputedForegroundColors[256][256][256];
WORD precomputedBackgroundColors[256][256][256];
bool colorsComputed = false;

void precomputeColors() {
    if (colorsComputed) return;
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            for (int k = 0; k < 256; ++k) {
                precomputedForegroundColors[i][j][k] = rgbToConsoleColor(i, j, k, false);
                precomputedBackgroundColors[i][j][k] = rgbToConsoleColor(i, j, k, true);
            }
        }
    }
    colorsComputed = true;
}

Graphics::Graphics(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    precomputeColors();
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    this->length = screenWidth * screenHeight;
    this->renderRectangle = SMALL_RECT{0, 0, 1, 1};
}

void Graphics::hijack() {
    SetConsoleWindowInfo(consoleHandle, TRUE, &renderRectangle);
    SetConsoleScreenBufferSize(consoleHandle, {(short) screenWidth, (short) screenWidth});
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

void Graphics::update(int x, int y, wchar_t new_character, int red, int green, int blue, bool background) {
    if (y < 0 || x < 0 || y > screenHeight || x > screenWidth)
        throw std::invalid_argument("x or y out of bounds: " + std::to_string(x) + " " + std::to_string(y));
    screen[y * screenWidth + x].Char.UnicodeChar = new_character;
    screen[y * screenWidth + x].Attributes = background ? precomputedBackgroundColors[red][green][blue]
                                                        : precomputedForegroundColors[red][green][blue];
}

void Graphics::fill(short x, short y) {
    if (!WriteConsoleOutputW(consoleHandle,
                             screen,
                             {(short) screenWidth, (short) screenHeight},
                             {x, y},
                             &renderRectangle))
        throw std::logic_error("WriteConsoleOutputW");
}
