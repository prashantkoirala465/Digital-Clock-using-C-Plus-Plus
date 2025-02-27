#include <iostream>       // For standard input and output.
#include "Clock.h"        // Include the Clock class to create and use a Clock object.
#include "Input.h"        // Include Input functions to get user input.
#include "Utility.h"      // Utility functions are indirectly used by Clock.

int main()
{
    // Print an ASCII art banner for the Digital Clock.
    std::cout << " __        __   _                            _ \n";
    std::cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___  | |\n";
    std::cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | |\n";
    std::cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/ |_|\n";
    std::cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___| (_)\n";
    std::cout << "\nWelcome to the Digital Clock!\n\n";

    // 1. Ask the user for their name.
    std::cout << "1. Enter your name: ";
    std::string userName;
    std::cin >> userName;  // Read the user's name from input.

    // 2. Get the user’s location using the Input class.
    std::string location = Input::getLocationInput();

    // 3. Ask the user which time format they prefer: 12-hour or 24-hour.
    int timeFormat = Input::getUserInput("3. Choose time format (12 or 24-hour): ", 12, 24);

    // 4. Ask if the user wants to display seconds.
    int displaySecChoice = Input::getUserInput("4. Display seconds? (1 for Yes, 0 for No): ", 0, 1);
    bool displaySeconds = (displaySecChoice == 1);  // Convert the integer choice to a boolean.

    // Create a Clock object with the provided information.
    // The Clock constructor also fetches the weather and logs the user’s choices.
    Clock clock(userName, location, timeFormat, displaySeconds);

    // Start the clock, which begins the continuous update loop.
    clock.start();

    return 0; // End the program. (Note: clock.start() contains an infinite loop, so this line is never reached.)
}
