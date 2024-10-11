#include "Graphics.h"

Graphics::Graphics(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                                              CONSOLE_TEXTMODE_BUFFER, NULL);
    this->screen = new wchar_t[screenWidth * screenHeight];
    this->screen[screenWidth * screenHeight - 1] = '\0';
    this->length = screenWidth * screenHeight;
}

Graphics::~Graphics() {
    delete[] screen;
}

void Graphics::hijack() {
    HWND consoleWindowHandle = GetConsoleWindow();

    RECT consoleDimensions;
    GetWindowRect(consoleWindowHandle, &consoleDimensions); //stores the console's current dimensions
    MoveWindow(consoleWindowHandle, consoleDimensions.left, consoleDimensions.top, screenWidth, screenHeight, TRUE);
    SetConsoleActiveScreenBuffer(consoleHandle);
    SetWindowLong(consoleWindowHandle, GWL_STYLE,
                  GetWindowLong(consoleWindowHandle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    DWORD mode;
    GetConsoleMode(consoleHandle, &mode);
    SetConsoleMode(consoleHandle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void Graphics::stop() {
    CloseHandle(consoleHandle);
}

void Graphics::update(int x, int y, wchar_t new_character) {
    if (y < 0 || x < 0 || y > screenHeight || x > screenWidth)
        throw std::invalid_argument("x or y out of bounds: " + std::to_string(x) + " " + std::to_string(y));
    screen[y * screenWidth + x] = new_character;
}

void Graphics::fill(short x, short y) {
    WriteConsoleOutputCharacterW(consoleHandle, screen, length, {x, y}, &bytesWritten);
}
