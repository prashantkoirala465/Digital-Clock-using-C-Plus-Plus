#include "Utility.h"
#include <fstream>
#include <ctime>
#include <cstring>
#include <iostream>

// For weather fetching
#include <curl/curl.h>

using namespace std;

// Existing time-zone functions
int Utility::getTimeZoneOffset(const std::string &location)
{
    if (location == "London")    return 1;
    if (location == "Berlin")    return 2;
    if (location == "Tokyo")     return 9;
    if (location == "Sydney")    return 10;
    if (location == "Kathmandu") return 5;
    return -9999; // invalid indicator
}

int Utility::getMinutesOffset(const std::string &location)
{
    // Kathmandu is UTC+5:45 => 5 hour offset + 45 min offset
    if (location == "Kathmandu")
    {
        return 45;
    }
    return 0;
}

// Logging function
void Utility::logUserChoice(const std::string &name,
                            const std::string &location,
                            int timeFormat,
                            bool displaySeconds)
{
    ofstream logFile("clock_log.txt", ios::app);
    if (!logFile)
    {
        // Could not open file
        return;
    }

    // Get current time as string
    time_t now = time(NULL);
    char *timeStr = ctime(&now);
    // Remove trailing newline if present
    if (timeStr && timeStr[strlen(timeStr) - 1] == '\n')
        timeStr[strlen(timeStr) - 1] = '\0';

    logFile << "User: " << name << "\n"
            << "Location: " << location << "\n"
            << "Time Format: " << timeFormat << "-hour\n"
            << "Display Seconds: " << (displaySeconds ? "Yes" : "No") << "\n"
            << "Timestamp: " << (timeStr ? timeStr : "N/A") << "\n"
            << "----------------------------------------\n";
    logFile.close();
}

// ----------------- WEATHER FETCHING -----------------
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Utility::getWeatherInfo(const std::string &location)
{
    // Replace spaces with plus signs (in case user typed multi-word city)
    std::string queryLocation = location;
    for (size_t i = 0; i < queryLocation.size(); i++)
    {
        if (queryLocation[i] == ' ')
            queryLocation[i] = '+';
    }

    // Construct the request URL (units=metric for Celsius)
    std::string apiKey = "494005be9c8a6ce8768382a85ce31f40"; // your API key
    std::string url = "http://api.openweathermap.org/data/2.5/weather?q="
                      + queryLocation
                      + "&appid=" + apiKey
                      + "&units=metric";

    // Initialize a CURL session
    CURL* curl = curl_easy_init();
    if (!curl)
    {
        return "Error initializing CURL.";
    }

    std::string readBuffer;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        return "Failed to get weather data.";
    }
    curl_easy_cleanup(curl);

    // A naive parse of the JSON to extract "temp" and "description"
    std::size_t tempPos = readBuffer.find("\"temp\":");
    std::size_t descPos = readBuffer.find("\"description\":");
    if (tempPos == std::string::npos || descPos == std::string::npos)
    {
        return "Could not parse weather data.";
    }

    // Extract temperature
    tempPos += 7; // move past "temp":
    std::size_t endTemp = readBuffer.find_first_of(",}", tempPos);
    std::string tempValue = readBuffer.substr(tempPos, endTemp - tempPos);

    // Extract description
    descPos += 14; // move past "description":"
    std::size_t endDesc = readBuffer.find("\"", descPos);
    std::string description = readBuffer.substr(descPos, endDesc - descPos);

    // Build final string: e.g. "19.32°C, scattered clouds"
    std::string weatherInfo = tempValue + "°C, " + description;
    return weatherInfo;
}

// ----------------- LOCAL DATE FORMATTING -----------------
std::string Utility::getLocalDate(const std::string &location)
{
    // Some sample formats for each city:
    // London  => DD/MM/YYYY
    // Berlin  => DD.MM.YYYY
    // Tokyo   => YYYY/MM/DD
    // Sydney  => DD/MM/YYYY
    // Kathmandu => DD/MM/YYYY
    // fallback => YYYY-MM-DD

    std::string dateFormat;
    if (location == "London")
        dateFormat = "%d/%m/%Y";  // e.g. "28/01/2025"
    else if (location == "Berlin")
        dateFormat = "%d.%m.%Y";  // e.g. "28.01.2025"
    else if (location == "Tokyo")
        dateFormat = "%Y/%m/%d";  // e.g. "2025/01/28"
    else if (location == "Sydney")
        dateFormat = "%d/%m/%Y";  // e.g. "28/01/2025"
    else if (location == "Kathmandu")
        dateFormat = "%d/%m/%Y";
    else
        dateFormat = "%Y-%m-%d";  // default

    // Get current UTC time
    time_t now = time(NULL);
    tm *t = gmtime(&now);

    // Apply city offset
    t->tm_hour += getTimeZoneOffset(location);
    t->tm_min  += getMinutesOffset(location);
    mktime(t);  // fix any rollover

    // Format using strftime
    char buffer[50];
    strftime(buffer, sizeof(buffer), dateFormat.c_str(), t);
    return std::string(buffer);
}
