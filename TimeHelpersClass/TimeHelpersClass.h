#ifndef TIME_HELPERS_H_
#define TIME_HELPERS_H_

#include <Arduino.h>
#include <chrono>
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
        String getCurrentLocalDateTime();
    private:
};

#endif