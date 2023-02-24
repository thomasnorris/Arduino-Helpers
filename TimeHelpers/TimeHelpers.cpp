#include "TimeHelpers.h"

std::chrono::time_point<std::chrono::system_clock> getTimeNow() {
  return std::chrono::system_clock::now();
}

double getElapsedTimeS(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end) {
  std::chrono::duration<double> elapsed_seconds = end - start;
  return elapsed_seconds.count();
}