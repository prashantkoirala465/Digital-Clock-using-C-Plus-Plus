#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display
{
private:
    static const int HEIGHT = 7;

    // Console color escape sequences
    static constexpr const char* FG_COLOR = "\033[1;32m";   // Bold Green
    static constexpr const char* RESET_COLOR = "\033[0m";   // Reset

    // Digit patterns
    static const std::string digits[10][HEIGHT];
    // Colon pattern
    static const std::string colon[HEIGHT];
    // AM/PM patterns
    static const std::string am[HEIGHT];
    static const std::string pm[HEIGHT];

public:
    // Clears the screen
    static void clearScreen();

    // Displays a single digit at x, y
    static void displayDigit(int digit, int x, int y);

    // Displays colon ':' at x, y
    static void displayColon(int x, int y);

    // Displays either AM or PM at x, y
    static void displayAmPm(bool isPm, int x, int y);
};

#endif
