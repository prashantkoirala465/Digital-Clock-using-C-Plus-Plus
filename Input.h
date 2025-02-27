#ifndef INPUT_H
#define INPUT_H

#include <string>

// The Input class provides functions to obtain and validate input from the user.
class Input
{
public:
    // Prompts the user with a message and reads an integer.
    // The valid input must be either minVal or maxVal.
    static int getUserInput(const std::string &prompt, int minVal, int maxVal);

    // Prompts the user to enter their location and validates it.
    static std::string getLocationInput();
};

#endif
