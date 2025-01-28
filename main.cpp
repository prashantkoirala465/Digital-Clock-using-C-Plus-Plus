#include <iostream>
#include "Clock.h"
#include "Input.h"
#include "Utility.h"

int main()
{
    std::cout << " __        __   _                            _ \n";
    std::cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___  | |\n";
    std::cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | |\n";
    std::cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/ |_|\n";
    std::cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___| (_)\n";
    std::cout << "\nWelcome to the Digital Clock!\n\n";

    // 1. Enter user name
    std::cout << "1. Enter your name: ";
    std::string userName;
    std::cin >> userName;

    // 2. Get location
    std::string location = Input::getLocationInput();

    // 3. Choose time format (12 or 24-hour)
    int timeFormat = Input::getUserInput("3. Choose time format (12 or 24-hour): ", 12, 24);

    // 4. Display seconds?
    int displaySecChoice = Input::getUserInput("4. Display seconds? (1 for Yes, 0 for No): ", 0, 1);
    bool displaySeconds = (displaySecChoice == 1);

    // Create Clock object (Weather is fetched automatically inside the constructor)
    Clock clock(userName, location, timeFormat, displaySeconds);

    // Start the clock loop
    clock.start();

    return 0;
}
