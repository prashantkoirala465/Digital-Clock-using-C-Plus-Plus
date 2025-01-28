#include "Input.h"
#include "Utility.h"
#include <iostream>
#include <limits>
using namespace std;

int Input::getUserInput(const std::string &prompt, int minVal, int maxVal)
{
    int input;
    while (true)
    {
        cout << prompt;
        cin >> input;

        // Validate input
        if (!cin.fail() && (input == minVal || input == maxVal))
        {
            // Clear the buffer
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        else
        {
            cout << "Invalid input. You can only select " << minVal << " or " << maxVal << "." << endl;
            // Clear error flags and discard invalid input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return input;
}

std::string Input::getLocationInput()
{
    while (true)
    {
        cout << "1. Enter your location (e.g., Sydney, Berlin, Tokyo, London, Kathmandu): ";
        string location;
        cin >> location;

        // Check if location is valid
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
