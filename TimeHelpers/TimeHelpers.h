#ifndef TIME_HELPERS_H_
#define TIME_HELPERS_H_

#include <Arduino.h>
#include <chrono>

std::chrono::time_point<std::chrono::system_clock> getTimeNow();
double getElapsedTimeS(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end);

#endif