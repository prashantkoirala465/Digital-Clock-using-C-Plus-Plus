#ifndef INPUT_H
#define INPUT_H

#include <string>

class Input
{
public:
    // Prompts the user and reads an integer that must be either minVal or maxVal
    static int getUserInput(const std::string &prompt, int minVal, int maxVal);

    // Prompts for a location and validates it
    static std::string getLocationInput();
};

#endif
