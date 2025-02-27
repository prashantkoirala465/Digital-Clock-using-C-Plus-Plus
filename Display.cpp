#include "Display.h"  // Include the Display class definition.
#include <iostream>   // For standard I/O operations.
#include <cstdio>     // For printf.
using namespace std;

// -------------------- DIGIT PATTERNS --------------------
// Each digit (0-9) is represented by a 7-line pattern of characters.
const std::string Display::digits[10][HEIGHT] = {
    {
        " ██████╗ ",
        "██╔═══██╗",
        "██║   ██║",
        "██║   ██║",
        "██║   ██║",
        "╚██████╔╝",
        " ╚═════╝ "
    },
    {
        " ██╗",
        "███║",
        "╚██║",
        " ██║",
        " ██║",
        " ██║",
        " ╚═╝"
    },
    {
        "██████╗ ",
        "╚════██╗",
        " █████╔╝",
        "██╔═══╝ ",
        "███████╗",
        "╚══════╝",
        "        "
    },
    {
        "██████╗ ",
        "╚════██╗",
        " █████╔╝",
        " ╚═══██╗",
        "██████╔╝",
        "╚═════╝ ",
        "        "
    },
    {
        "██╗  ██╗",
        "██║  ██║",
        "███████║",
        "╚════██║",
        "     ██║",
        "     ╚═╝",
        "        "
    },
    {
        "███████╗",
        "██╔════╝",
        "███████╗",
        "╚════██║",
        "███████║",
        "╚══════╝",
        "        "
    },
    {
        " ██████╗ ",
        "██╔════╝ ",
        "███████╗ ",
        "██╔═══██╗",
        "╚██████╔╝",
        " ╚═════╝ ",
        "         "
    },
    {
        "███████╗",
        "╚════██║",
        "    ██╔╝",
        "   ██╔╝ ",
        "  ██╔╝  ",
        "  ╚═╝   ",
        "        "
    },
    {
        " █████╗ ",
        "██╔══██╗",
        "╚█████╔╝",
        "██╔══██╗",
        "╚█████╔╝",
        " ╚════╝ ",
        "        "
    },
    {
        " █████╗ ",
        "██╔══██╗",
        "╚██████║",
        " ╚═══██║",
        " █████╔╝",
        " ╚════╝ ",
        "        "
    }
};

// -------------------- COLON AND AM/PM PATTERNS --------------------
// Pattern for the colon ":" used between hour and minute.
const std::string Display::colon[HEIGHT] = {
    "    ",
    "  ▀ ",
    "  ▀  ",
    "     ",
    "  ▀  ",
    "  ▀  ",
    "     "
};

// Pattern for "AM" displayed in large text.
const std::string Display::am[HEIGHT] = {
    " █████╗ ███╗   ███╗",
    "██╔══██╗████╗ ████║",
    "███████║██╔████╔██║",
    "██╔══██║██║╚██╔╝██║",
    "██║  ██║██║ ╚═╝ ██║",
    "╚═╝  ╚═╝╚═╝     ╚═╝",
    "                   "
};

// Pattern for "PM" displayed in large text.
const std::string Display::pm[HEIGHT] = {
    "██████╗ ███╗   ███╗",
    "██╔══██╗████╗ ████║",
    "██████╔╝██╔████╔██║",
    "██╔═══╝ ██║╚██╔╝██║",
    "██║     ██║ ╚═╝ ██║",
    "╚═╝     ╚═╝     ╚═╝",
    "                   "
};

// clearScreen() clears the console using ANSI escape codes.
void Display::clearScreen()
{
    printf("\033[2J"); // Clears the screen.
    printf("\033[H");  // Moves the cursor to the top-left corner.
}

// displayDigit() prints a single digit (using its ASCII art) at the given x and y coordinates.
void Display::displayDigit(int digit, int x, int y)
{
    // Loop through each line of the digit pattern.
    for (int i = 0; i < HEIGHT; i++)
    {
        // Move the cursor to the correct position.
        printf("\033[%d;%dH", y + i, x);
        // Print the line with a set foreground color and then reset the color.
        printf("%s%s%s", FG_COLOR, digits[digit][i].c_str(), RESET_COLOR);
    }
}

// displayColon() prints the colon pattern at the specified coordinates.
void Display::displayColon(int x, int y)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        printf("%s%s%s", FG_COLOR, colon[i].c_str(), RESET_COLOR);
    }
}

// displayAmPm() prints either "AM" or "PM" at the given coordinates based on the isPm flag.
void Display::displayAmPm(bool isPm, int x, int y)
{
    const std::string* pattern = isPm ? pm : am; // Choose PM if true, else AM.
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        printf("%s%s%s", FG_COLOR, pattern[i].c_str(), RESET_COLOR);
    }
}
