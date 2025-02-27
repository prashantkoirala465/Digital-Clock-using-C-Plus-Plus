#ifndef CLOCK_H              // If CLOCK_H is not defined, then define it.
#define CLOCK_H

#include <string>           // Include string to use std::string.

// The Clock class handles user settings, time calculations, and updating the display continuously.
class Clock
{
private:
    std::string userName;    // Stores the user’s name.
    std::string location;    // Stores the location (e.g., London, Tokyo) for time zone and weather purposes.
    int timeFormat;          // Stores the time format: 12 for 12-hour or 24 for 24-hour format.
    bool displaySeconds;     // Indicates whether seconds should be displayed.
    int timeZoneOffset;      // Stores the hour offset from UTC for the given location.
    int minuteOffset;        // Stores any additional minute offset (for cities with non-whole hour offsets).

    // Stores the weather information fetched from the internet.
    std::string weatherInfo;

public:
    // Constructor: Initializes the Clock with the provided user settings.
    Clock(const std::string &userName,
          const std::string &location,
          int timeFormat,
          bool displaySeconds);

    // The start() method enters an infinite loop to continuously update the clock display.
    void start();
};

#endif  // End of CLOCK_H definition.
