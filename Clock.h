#ifndef CLOCK_H
#define CLOCK_H

#include <string>

class Clock
{
private:
    std::string userName;
    std::string location;
    int timeFormat;          // 12 or 24
    bool displaySeconds;
    int timeZoneOffset;
    int minuteOffset;

    // Store fetched weather info
    std::string weatherInfo;

public:
    // Constructor
    Clock(const std::string &userName,
          const std::string &location,
          int timeFormat,
          bool displaySeconds);

    // Starts the clock loop (displays time continuously)
    void start();
};

#endif
