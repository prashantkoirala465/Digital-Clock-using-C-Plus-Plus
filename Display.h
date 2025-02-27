#ifndef DISPLAY_H           // If DISPLAY_H is not defined, then define it.
#define DISPLAY_H

#include <string>          // Include string to use std::string in our class.

// The Display class handles drawing the clock’s digits and symbols on the console.
class Display
{
private:
    static const int HEIGHT = 7;  // Each digit or symbol is 7 lines tall.

    // ANSI escape codes for colored output:
    // FG_COLOR sets the text to bold green.
    static constexpr const char* FG_COLOR = "\033[1;32m";
    // RESET_COLOR resets the text color to the terminal's default.
    static constexpr const char* RESET_COLOR = "\033[0m";

    // ASCII art patterns for digits 0-9.
    static const std::string digits[10][HEIGHT];
    // Pattern for the colon.
    static const std::string colon[HEIGHT];
    // Patterns for the "AM" and "PM" indicators.
    static const std::string am[HEIGHT];
    static const std::string pm[HEIGHT];

public:
    // Clears the console screen.
    static void clearScreen();

    // Displays a single digit at the (x, y) position.
    static void displayDigit(int digit, int x, int y);

    // Displays a colon at the (x, y) position.
    static void displayColon(int x, int y);

    // Displays either "AM" or "PM" at the (x, y) position.
    static void displayAmPm(bool isPm, int x, int y);
};

#endif  // End of DISPLAY_H definition.
