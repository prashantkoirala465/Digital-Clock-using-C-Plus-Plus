#include "Utility.h"   // Include the Utility class definition.
#include <fstream>     // For file operations (logging).
#include <ctime>       // For working with time.
#include <cstring>     // For string manipulation (e.g., strlen).
#include <iostream>    // For standard I/O.

// For fetching weather information.
#include <curl/curl.h>

using namespace std;

// getTimeZoneOffset() returns the hour offset from UTC for a given location.
int Utility::getTimeZoneOffset(const std::string &location)
{
    if (location == "London")    return 0;   // UTC+1
    if (location == "Berlin")    return 1;   // UTC+1
    if (location == "Tokyo")     return 9;   // UTC+9
    if (location == "Sydney")    return 11;  // UTC+11
    if (location == "Kathmandu") return 5;   // UTC+5:45 (hour component)
    return -9999; // Invalid location indicator.
}

// getMinutesOffset() returns any additional minute offset.
// For example, Kathmandu is UTC+5:45 (5 hours plus 45 minutes).
int Utility::getMinutesOffset(const std::string &location)
{
    if (location == "Kathmandu")
    {
        return 45;
    }
    return 0;
}

// logUserChoice() writes the user's settings to a log file.
void Utility::logUserChoice(const std::string &name,
                            const std::string &location,
                            int timeFormat,
                            bool displaySeconds)
{
    // Open (or create) the log file in append mode.
    ofstream logFile("clock_log.txt", ios::app);
    if (!logFile)
    {
        // If the file cannot be opened, exit the function.
        return;
    }

    // Get the current time and convert it to a string.
    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    // Remove the trailing newline character from the time string.
    if (timeStr && timeStr[strlen(timeStr) - 1] == '\n')
        timeStr[strlen(timeStr) - 1] = '\0';

    // Write the user information and timestamp to the file.
    logFile << "User: " << name << "\n"
            << "Location: " << location << "\n"
            << "Time Format: " << timeFormat << "-hour\n"
            << "Display Seconds: " << (displaySeconds ? "Yes" : "No") << "\n"
            << "Timestamp: " << (timeStr ? timeStr : "N/A") << "\n"
            << "----------------------------------------\n";
    logFile.close();
}

// ----------------- WEATHER FETCHING -----------------

// WriteCallback() is a helper function for cURL to collect the response data.
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    // Append the received data to the provided string.
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// getWeatherInfo() fetches weather data for the given location using the OpenWeatherMap API.
std::string Utility::getWeatherInfo(const std::string &location)
{
    // Replace spaces in the location with '+' for the URL.
    std::string queryLocation = location;
    for (size_t i = 0; i < queryLocation.size(); i++)
    {
        if (queryLocation[i] == ' ')
            queryLocation[i] = '+';
    }

    // Construct the API URL. (The API key is hard-coded for this example.)
    std::string apiKey = "494005be9c8a6ce8768382a85ce31f40"; // Your API key.
    std::string url = "http://api.openweathermap.org/data/2.5/weather?q="
                      + queryLocation
                      + "&appid=" + apiKey
                      + "&units=metric";

    // Initialize a cURL session.
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        return "Error initializing CURL.";
    }

    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    // Set the callback function to handle the incoming data.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // Provide the string to store the data.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    // Execute the HTTP request.
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "Failed to get weather data.";
    }
    curl_easy_cleanup(curl);

    // Naively parse the JSON response to extract "temp" and "description".
    std::size_t tempPos = readBuffer.find("\"temp\":");
    std::size_t descPos = readBuffer.find("\"description\":");
    if (tempPos == std::string::npos || descPos == std::string::npos)
    {
        return "Could not parse weather data.";
    }

    // Extract the temperature value.
    tempPos += 7; // Skip past "temp":
    std::size_t endTemp = readBuffer.find_first_of(",}", tempPos);
    std::string tempValue = readBuffer.substr(tempPos, endTemp - tempPos);

    // Extract the weather description.
    descPos += 14; // Skip past "description":"
    std::size_t endDesc = readBuffer.find("\"", descPos);
    std::string description = readBuffer.substr(descPos, endDesc - descPos);

    // Combine the temperature and description into a single string.
    std::string weatherInfo = tempValue + "°C, " + description;
    return weatherInfo;
}

// ----------------- LOCAL DATE FORMATTING -----------------

// getLocalDate() formats and returns today's date according to the local customs of the specified location.
std::string Utility::getLocalDate(const std::string &location)
{
    // Set different date formats based on the location.
    std::string dateFormat;
    if (location == "London")
        dateFormat = "%d/%m/%Y";  // e.g., "28/01/2025"
    else if (location == "Berlin")
        dateFormat = "%d.%m.%Y";  // e.g., "28.01.2025"
    else if (location == "Tokyo")
        dateFormat = "%Y/%m/%d";  // e.g., "2025/01/28"
    else if (location == "Sydney")
        dateFormat = "%d/%m/%Y";  // e.g., "28/01/2025"
    else if (location == "Kathmandu")
        dateFormat = "%d/%m/%Y";
    else
        dateFormat = "%Y-%m-%d";  // Default format.

    // Get the current UTC time.
    time_t now = time(NULL);
    tm *t = gmtime(&now);

    // Adjust the time for the location.
    t->tm_hour += getTimeZoneOffset(location);
    t->tm_min  += getMinutesOffset(location);
    mktime(t);  // Correct for any rollover (e.g., if minutes exceed 59).

    // Format the time into a string.
    char buffer[50];
    strftime(buffer, sizeof(buffer), dateFormat.c_str(), t);
    return std::string(buffer);
}
