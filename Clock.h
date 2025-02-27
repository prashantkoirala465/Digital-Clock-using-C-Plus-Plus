#ifndef CLOCK_H
#define CLOCK_H

#include <string>

// The Clock class handles user settings, time calculation, and the display loop.
class Clock
{
private:
    std::string userName;    // User’s name.
    std::string location;    // Location (e.g., London, Tokyo).
    int timeFormat;          // Time format: 12 or 24 hours.
    bool displaySeconds;     // Whether to show seconds.
    int timeZoneOffset;      // Hour offset based on location.
    int minuteOffset;        // Minute offset (for non-whole hour differences).

    // Weather information fetched from the internet.
    std::string weatherInfo;

public:
    // Constructor: Initializes the clock with the user’s preferences.
    Clock(const std::string &userName,
          const std::string &location,
          int timeFormat,
          bool displaySeconds);

    // Starts the continuous clock loop (updating the display every second).
    void start();
};

#endif
