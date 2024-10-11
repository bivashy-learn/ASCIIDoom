#include "Graphics.h"

Graphics::Graphics(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
}

void Graphics::hijack() {
    HWND consoleWindowHandle = GetConsoleWindow();
    RECT consoleDimensions;
    GetWindowRect(consoleWindowHandle, &consoleDimensions); //stores the console's current dimensions
    MoveWindow(consoleWindowHandle, consoleDimensions.left, consoleDimensions.top, screenWidth, screenHeight, TRUE);
    SetConsoleActiveScreenBuffer(consoleHandle);
    SetWindowLong(consoleWindowHandle, GWL_STYLE, GetWindowLong(consoleWindowHandle, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void Graphics::stop() {
    CloseHandle(consoleHandle);
}

void Graphics::fill(const wchar_t *rawMap, int length, short x, short y) {
    WriteConsoleOutputCharacterW(consoleHandle, rawMap, length, {x, y}, &bytesWritten);
}

HANDLE Graphics::getConsoleHandle() {
    return consoleHandle;
}