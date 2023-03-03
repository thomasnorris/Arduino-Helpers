#ifndef TIME_HELPERS_H_
#define TIME_HELPERS_H_

/* Library Requirements */
// https://github.com/arduino-libraries/NTPClient
// ESP8266WiFi

#include <Arduino.h>
#include <chrono>
#include <string>
#include <sstream>
#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeHelpers {
    public:
        TimeHelpers();
        std::chrono::time_point<std::chrono::system_clock> getClockTimeNow();
        double getElapsedTimeS(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);
        String prettyFormatS(int seconds);
        void begin();
        void update();
        String getCurrentLocalDateTime24hr();
        String getCurrentLocalDateTime12hr();
    private:
        String getFormattedTime();
};

#endif