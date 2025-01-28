# Digital Clock with Weather Integration

A feature-rich console-based digital clock application that displays time in beautiful ASCII art format along with local weather information. The clock supports multiple time zones, 12/24-hour formats, and real-time weather updates.

## Features

- **Beautiful ASCII Art Display**: Time is displayed using custom-designed ASCII art characters
- **Dual Time Format**: Support for both 12-hour and 24-hour time formats
- **Weather Integration**: Real-time weather information for the specified location
- **Time Zone Support**: Ability to display time for different time zones
- **Configurable Display**: Option to show/hide seconds
- **User Preferences**: Saves user preferences for future sessions
- **Date Display**: Shows current date for the selected location
- **Color Output**: Uses ANSI colors for enhanced visibility

## Requirements

- C++ compiler with C++11 support
- Standard C++ libraries
- ANSI-compatible terminal

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/alexbytesback/Digital-Clock-using-C-Plus-Plus
   cd Digital-Clock-using-C-Plus-Plus
   ```

2. Compile the project:
   ```bash
   g++ -std=c++17 main.cpp Clock.cpp Display.cpp Input.cpp Utility.cpp -o DigitalClock
   ```

## Usage

1. Run the compiled program:
   ```bash
   ./DigitalClock
   ```

2. Follow the prompts to:
   - Enter your name
   - Select your location
   - Choose time format (12/24 hour)
   - Toggle seconds display

## Code Structure

- `main.cpp`: Entry point of the application
- `Clock.h/cpp`: Core clock functionality and main display loop
- `Display.h/cpp`: ASCII art rendering and screen management
- `Input.h/cpp`: User input handling and validation
- `Utility.h/cpp`: Helper functions for time zones and weather

## Display Features

- Large, clear ASCII art digits
- Blinking colon separator
- AM/PM indicator for 12-hour format
- Color-coded output for better visibility
- Weather information display
- Current date display

## Configuration

The application stores user preferences in `clock_log.txt`, including:
- Username
- Preferred location
- Time format choice
- Seconds display preference

## Technical Details

- Written in C++
- Uses ANSI escape sequences for terminal manipulation
- Custom ASCII art patterns for digits and symbols
- Real-time updates with 1-second refresh rate
- Efficient screen clearing and cursor positioning
- Time zone and weather data integration

## Contributing

Contributions are welcome! Please feel free to submit pull requests.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
