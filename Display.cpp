#include "Display.h"
#include <iostream>  // for std::cout
#include <cstdio>    // for printf
using namespace std;

// Initialize static members:
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

const std::string Display::colon[HEIGHT] = {
    "    ",
    "  ▀ ",
    "  ▀  ",
    "     ",
    "  ▀  ",
    "  ▀  ",
    "     "
};

const std::string Display::am[HEIGHT] = {
    " █████╗ ███╗   ███╗",
    "██╔══██╗████╗ ████║",
    "███████║██╔████╔██║",
    "██╔══██║██║╚██╔╝██║",
    "██║  ██║██║ ╚═╝ ██║",
    "╚═╝  ╚═╝╚═╝     ╚═╝",
    "                   "
};

const std::string Display::pm[HEIGHT] = {
    "██████╗ ███╗   ███╗",
    "██╔══██╗████╗ ████║",
    "██████╔╝██╔████╔██║",
    "██╔═══╝ ██║╚██╔╝██║",
    "██║     ██║ ╚═╝ ██║",
    "╚═╝     ╚═╝     ╚═╝",
    "                   "
};

void Display::clearScreen()
{
    // ANSI escape codes to clear screen and move cursor to (0,0)
    printf("\033[2J");
    printf("\033[H");
}

void Display::displayDigit(int digit, int x, int y)
{
    // Print each line of the digit at the specified (x, y)
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        printf("%s%s%s", FG_COLOR, digits[digit][i].c_str(), RESET_COLOR);
    }
}

void Display::displayColon(int x, int y)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        printf("%s%s%s", FG_COLOR, colon[i].c_str(), RESET_COLOR);
    }
}

void Display::displayAmPm(bool isPm, int x, int y)
{
    const std::string* pattern = isPm ? pm : am;
    for (int i = 0; i < HEIGHT; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        printf("%s%s%s", FG_COLOR, pattern[i].c_str(), RESET_COLOR);
    }
}
