#include "Input.h"      // Include the Input class declaration.
#include "Utility.h"    // Include Utility functions (for validating location).
#include <iostream>     // For input/output operations.
#include <limits>       // For clearing the input buffer.
using namespace std;

// getUserInput() prompts the user and reads an integer.
// It ensures that the user only enters one of the allowed values (minVal or maxVal).
int Input::getUserInput(const std::string &prompt, int minVal, int maxVal)
{
    int input;
    while (true)
    {
        cout << prompt;
        cin >> input;

        // Validate that input is correct (not a failure) and matches one of the allowed values.
        if (!cin.fail() && (input == minVal || input == maxVal))
        {
            // Clear any extra characters from the input.
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        else
        {
            // Tell the user the input was invalid and prompt again.
            cout << "Invalid input. You can only select " << minVal << " or " << maxVal << "." << endl;
            // Clear the error state and discard the bad input.
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return input;
}

// getLocationInput() prompts the user to enter their location.
// It uses Utility::getTimeZoneOffset to check if the location is valid.
std::string Input::getLocationInput()
{
    while (true)
    {
        cout << "1. Enter your location (e.g., Sydney, Berlin, Tokyo, London, Kathmandu): ";
        string location;
        cin >> location;

        // If the location returns a valid time zone offset, accept it.
        if (Utility::getTimeZoneOffset(location) != -9999)
        {
            return location;
        }
        else
        {
            cout << "Invalid location. Please enter a valid location.\n";
        }
    }
}
