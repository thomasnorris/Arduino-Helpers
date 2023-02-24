#include "TimeHelpers.h"

std::chrono::time_point<std::chrono::system_clock> getTimeNow() {
  return std::chrono::system_clock::now();
}

double getElapsedTimeS(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end) {
  std::chrono::duration<double> elapsed_seconds = end - start;
  return elapsed_seconds.count();
}

String formatSeconds(int seconds) {
  int minutes = seconds / 60;
  int hours = minutes / 60;

  int rem_seconds = int(seconds % 60);
  int rem_minutes = int(minutes % 60);
  int rem_hours = int(hours % 60);

  if (rem_hours == 0) {
    if (rem_minutes == 0) {
      return String(rem_seconds) + "s";
    }

    if (rem_seconds == 0) {
      return String(rem_minutes) + "m ";
    }

    return String(rem_minutes) + "m " + String(rem_seconds) + "s";
  }

  return String(rem_hours) + "h " + String(rem_minutes) + "m " + String(rem_seconds) + "s";
}