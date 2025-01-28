#include "Clock.h"
#include "Display.h"
#include "Utility.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdio>   // for printf

using namespace std;

Clock::Clock(const std::string &uName,
             const std::string &loc,
             int format,
             bool dispSec)
    : userName(uName),
      location(loc),
      timeFormat(format),
      displaySeconds(dispSec)
{
    // 1. Calculate offsets
    timeZoneOffset = Utility::getTimeZoneOffset(location);
    minuteOffset   = Utility::getMinutesOffset(location);

    // 2. Log user preferences
    Utility::logUserChoice(userName, location, timeFormat, displaySeconds);

    // 3. Fetch weather once and store in weatherInfo
    weatherInfo = Utility::getWeatherInfo(location);
}

void Clock::start()
{
    while (true)
    {
        // Clear screen
        Display::clearScreen();

        // Get current UTC time
        time_t now = time(NULL);
        tm *t = gmtime(&now);

        // Apply offset
        t->tm_hour += timeZoneOffset;
        t->tm_min  += minuteOffset;

        // Let mktime() fix any out-of-range values
        mktime(t);

        int hour   = t->tm_hour;
        int minute = t->tm_min;
        int second = t->tm_sec;

        bool isPm = false;
        if (timeFormat == 12)
        {
            isPm = (hour >= 12);
            hour = hour % 12;
            if (hour == 0) hour = 12;
        }

        // -------------------- DISPLAY TIME --------------------
        Display::displayDigit(hour / 10, 10, 5);
        Display::displayDigit(hour % 10, 18, 5);

        // Colon
        Display::displayColon(26, 5);

        Display::displayDigit(minute / 10, 34, 5);
        Display::displayDigit(minute % 10, 42, 5);

        if (displaySeconds)
        {
            Display::displayColon(50, 5);
            Display::displayDigit(second / 10, 58, 5);
            Display::displayDigit(second % 10, 66, 5);
        }

        // AM/PM label if 12-hour
        if (timeFormat == 12)
        {
            Display::displayAmPm(isPm, 80, 5);
        }

        // -------------------- DISPLAY DATE --------------------
        // Get local date for the chosen location
        std::string localDate = Utility::getLocalDate(location);

        // Print the date in, say, row=15, col=10
        printf("\033[%d;%dH", 15, 10);
        printf("\033[1;33mToday in %s: %s\033[0m\n", location.c_str(), localDate.c_str());

        // -------------------- DISPLAY WEATHER --------------------
        // Print the stored weather info on row=17, col=10
        printf("\033[%d;%dH", 17, 10);
        printf("\033[1;32mWeather: %s\033[0m\n", weatherInfo.c_str());

        fflush(stdout);

        // Sleep for 1 second
        this_thread::sleep_for(chrono::seconds(1));
    }
}
