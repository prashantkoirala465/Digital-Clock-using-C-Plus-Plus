#include "Clock.h"         // Include the Clock class definition.
#include "Display.h"       // Include the Display class (used to show digits, colon, AM/PM).
#include "Utility.h"       // Include helper functions (for time zones, weather, and logging).
#include <iostream>        // For input and output.
#include <ctime>           // For working with time.
#include <thread>          // For sleep functionality.
#include <chrono>          // For time durations (e.g., seconds).
#include <cstdio>          // For printf (printing formatted text).

using namespace std;

// Constructor for the Clock class.
// It initializes user preferences and calculates the time offsets based on location.
Clock::Clock(const std::string &uName,
             const std::string &loc,
             int format,
             bool dispSec)
    : userName(uName),         // Initialize the user name.
      location(loc),           // Initialize the location.
      timeFormat(format),      // Set the time format (12-hour or 24-hour).
      displaySeconds(dispSec)  // Determine if seconds should be displayed.
{
    // 1. Calculate offsets for time zone and minutes.
    timeZoneOffset = Utility::getTimeZoneOffset(location);
    minuteOffset   = Utility::getMinutesOffset(location);

    // 2. Log the user’s preferences to a file.
    Utility::logUserChoice(userName, location, timeFormat, displaySeconds);

    // 3. Fetch the weather information for the location (this happens once).
    weatherInfo = Utility::getWeatherInfo(location);
}

// The start() function contains an infinite loop that updates the clock every second.
void Clock::start()
{
    while (true)  // Loop forever until the program is stopped.
    {
        // Clear the console screen before re-drawing the time.
        Display::clearScreen();

        // Get the current UTC time.
        time_t now = time(NULL);
        tm *t = gmtime(&now);  // Convert to a UTC time structure.

        // Apply the time zone and minute offsets (to convert UTC to local time).
        t->tm_hour += timeZoneOffset;
        t->tm_min  += minuteOffset;

        // mktime() fixes any values that might be out of normal range (like minutes over 59).
        mktime(t);

        // Extract the hour, minute, and second from the time structure.
        int hour   = t->tm_hour;
        int minute = t->tm_min;
        int second = t->tm_sec;

        // For 12-hour format, determine if it is AM or PM.
        bool isPm = false;
        if (timeFormat == 12)
        {
            isPm = (hour >= 12);
            hour = hour % 12;  // Convert to 12-hour format.
            if (hour == 0) hour = 12; // In a 12-hour clock, 0 is represented as 12.
        }

        // -------------------- DISPLAY TIME --------------------
        // Display the hour digits:
        Display::displayDigit(hour / 10, 10, 5);   // Tens place of the hour.
        Display::displayDigit(hour % 10, 18, 5);   // Ones place of the hour.

        // Display a colon (:) between hours and minutes.
        Display::displayColon(26, 5);

        // Display the minute digits:
        Display::displayDigit(minute / 10, 34, 5);  // Tens place of the minute.
        Display::displayDigit(minute % 10, 42, 5);  // Ones place of the minute.

        // Optionally display seconds if the user chose to.
        if (displaySeconds)
        {
            Display::displayColon(50, 5);
            Display::displayDigit(second / 10, 58, 5);
            Display::displayDigit(second % 10, 66, 5);
        }

        // If 12-hour format is selected, display the AM/PM indicator.
        if (timeFormat == 12)
        {
            Display::displayAmPm(isPm, 80, 5);
        }

        // -------------------- DISPLAY DATE --------------------
        // Get the local date (formatted according to location).
        std::string localDate = Utility::getLocalDate(location);

        // Move the cursor to a specific position (row 15, column 10) and print the date.
        printf("\033[%d;%dH", 15, 10);
        printf("\033[1;33mToday in %s: %s\033[0m\n", location.c_str(), localDate.c_str());

        // -------------------- DISPLAY WEATHER --------------------
        // Move the cursor to row 17, column 10 and display the weather information.
        printf("\033[%d;%dH", 17, 10);
        printf("\033[1;32mWeather: %s\033[0m\n", weatherInfo.c_str());

        fflush(stdout);  // Ensure all output is printed immediately.

        // Pause the program for 1 second before updating the display.
        this_thread::sleep_for(chrono::seconds(1));
    }
}
