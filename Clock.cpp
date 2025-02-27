#include "Clock.h"         // Include the Clock class declaration so we know what functions and variables belong to Clock.
#include "Display.h"       // Include the Display class for drawing digits and symbols on the screen.
#include "Utility.h"       // Include Utility functions that help with time zones, weather data, and logging.
#include <iostream>        // Include the iostream library for standard input/output operations.
#include <ctime>           // Include ctime for working with time functions (e.g., getting the current time).
#include <thread>          // Include thread to allow us to pause the program (sleep functionality).
#include <chrono>          // Include chrono to work with time durations, such as seconds.
#include <cstdio>          // Include cstdio for using printf, which prints formatted text.

using namespace std;       // Allows us to use names from the std (standard) namespace without the std:: prefix.
// Constructor for the Clock class.
// It initializes user preferences and calculates the time offsets based on location.
Clock::Clock(const std::string &uName,
             const std::string &loc,
             int format,
             bool dispSec)
    : userName(uName),         // Initialize the userName member with the passed value uName.
      location(loc),           // Initialize the location member with loc.
      timeFormat(format),      // Set the timeFormat (either 12 or 24) using format.
      displaySeconds(dispSec)  // Determine whether to display seconds (true/false) from dispSec.
{
    // 1. Calculate offsets for time zone and minutes.
    // The timeZoneOffset tells us how many hours to add to UTC to get the local time.
    timeZoneOffset = Utility::getTimeZoneOffset(location);
    // The minuteOffset handles cases where the offset is not a whole hour (like Kathmandu, which is +45 minutes).
    minuteOffset   = Utility::getMinutesOffset(location);

    // 2. Log the user’s preferences to a file.
    // This function writes the user's choices (name, location, format, and seconds option) into a log file.
    Utility::logUserChoice(userName, location, timeFormat, displaySeconds);

    // 3. Fetch the weather information for the location.
    // This gets the current weather details (like temperature and description) and stores it in weatherInfo.
    weatherInfo = Utility::getWeatherInfo(location);
}
// The start() function contains an infinite loop that updates the clock every second.
void Clock::start()
{
    while (true)  // This loop runs forever until you manually stop the program.
    {
        // Clear the console screen before re-drawing the time.
        // This avoids printing new output on top of the old, creating a "refresh" effect.
        Display::clearScreen();

        // Get the current time in UTC (Coordinated Universal Time).
        time_t now = time(NULL);  // time(NULL) returns the current time as a time_t type.
        tm *t = gmtime(&now);     // Convert the time_t value into a tm structure (broken-down time in UTC).

        // Apply the time zone and minute offsets (to convert UTC to local time).
        t->tm_hour += timeZoneOffset;  // Adjust the hours by adding the location's time zone offset.
        t->tm_min  += minuteOffset;    // Adjust the minutes by adding any extra minutes (if applicable).

        // mktime() fixes any out-of-range values.
        // For example, if t->tm_min exceeds 59, mktime() will increment the hour accordingly.
        mktime(t);

        // Extract the current hour, minute, and second from the tm structure.
        int hour   = t->tm_hour;
        int minute = t->tm_min;
        int second = t->tm_sec;

        // For 12-hour format, we need to adjust the hour and determine AM or PM.
        bool isPm = false;
        if (timeFormat == 12)
        {
            isPm = (hour >= 12);      // If the hour is 12 or more, it's PM.
            hour = hour % 12;         // Convert hour from 24-hour to 12-hour format.
            if (hour == 0) hour = 12;   // In 12-hour format, 0 is represented as 12.
        }

        // -------------------- DISPLAY TIME --------------------
        // The following lines call Display functions to draw each part of the clock.

        // Display the hour digits:
        Display::displayDigit(hour / 10, 10, 5);   // Display the tens digit of the hour at column 10, row 5.
        Display::displayDigit(hour % 10, 18, 5);   // Display the ones digit of the hour at column 18, row 5.

        // Display a colon (:) between hours and minutes.
        Display::displayColon(26, 5);              // Draw the colon at column 26, row 5.

        // Display the minute digits:
        Display::displayDigit(minute / 10, 34, 5);  // Draw the tens digit of the minute at column 34, row 5.
        Display::displayDigit(minute % 10, 42, 5);  // Draw the ones digit of the minute at column 42, row 5.

        // Optionally display seconds if the user chose to show them.
        if (displaySeconds)
        {
            Display::displayColon(50, 5);          // Draw another colon for seconds at column 50, row 5.
            Display::displayDigit(second / 10, 58, 5); // Draw the tens digit of the seconds at column 58, row 5.
            Display::displayDigit(second % 10, 66, 5); // Draw the ones digit of the seconds at column 66, row 5.
        }

        // If the clock is in 12-hour format, display the AM/PM indicator.
        if (timeFormat == 12)
        {
            Display::displayAmPm(isPm, 80, 5);       // Draw either "AM" or "PM" at column 80, row 5.
        }

        // -------------------- DISPLAY DATE --------------------
        // Get the local date formatted based on the location.
        std::string localDate = Utility::getLocalDate(location);

        // Use ANSI escape sequences to move the cursor to row 15, column 10,
        // then print the date in a specific color (here, yellow is used).
        printf("\033[%d;%dH", 15, 10);
        printf("\033[1;33mToday in %s: %s\033[0m\n", location.c_str(), localDate.c_str());

        // -------------------- DISPLAY WEATHER --------------------
        // Move the cursor to row 17, column 10 and print the weather info.
        printf("\033[%d;%dH", 17, 10);
        printf("\033[1;32mWeather: %s\033[0m\n", weatherInfo.c_str());

        fflush(stdout);  // Flush the output buffer to ensure everything is printed immediately.

        // Pause for 1 second before the loop runs again.
        this_thread::sleep_for(chrono::seconds(1));
    }
}
