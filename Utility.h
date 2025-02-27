#ifndef UTILITY_H         // If UTILITY_H is not defined, define it.
#define UTILITY_H

#include <string>        // Include string to work with std::string.

// The Utility class provides helper functions for:
// - Determining time zone offsets
// - Logging user choices
// - Fetching weather data
// - Formatting dates
class Utility
{
public:
    // Returns the hour offset from UTC for the given location.
    static int getTimeZoneOffset(const std::string &location);
    // Returns any additional minute offset for the given location.
    static int getMinutesOffset(const std::string &location);

    // Logs the user’s settings (name, location, time format, seconds option) to a file.
    static void logUserChoice(const std::string &name,
                              const std::string &location,
                              int timeFormat,
                              bool displaySeconds);

    // Fetches weather information (temperature and description) for the given location.
    static std::string getWeatherInfo(const std::string &location);

    // Returns today's date formatted for the given location.
    static std::string getLocalDate(const std::string &location);
};

#endif  // End of UTILITY_H definition.
