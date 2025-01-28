#ifndef UTILITY_H
#define UTILITY_H

#include <string>

class Utility
{
public:
    static int getTimeZoneOffset(const std::string &location);
    static int getMinutesOffset(const std::string &location);

    static void logUserChoice(const std::string &name,
                              const std::string &location,
                              int timeFormat,
                              bool displaySeconds);

    // Fetch weather info (temp + description) for the given location
    // using OpenWeatherMap API.
    static std::string getWeatherInfo(const std::string &location);

    // Return today's date in the local format for each location
    static std::string getLocalDate(const std::string &location);
};

#endif
