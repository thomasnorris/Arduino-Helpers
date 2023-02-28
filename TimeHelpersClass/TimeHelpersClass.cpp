#include "TimeHelpersClass.h"

char _days_of_the_week[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
WiFiUDP _ntpUDP;

// set NTPClient to EST time zone (UTC -5 Hours)
long _utc_time_seconds = -5 * 3600;
NTPClient _timeClient(_ntpUDP, "north-america.pool.ntp.org", _utc_time_seconds);

// public
TimeHelpers::TimeHelpers() {
  // nothing
}

void TimeHelpers::begin() {
  _timeClient.begin();
}

void TimeHelpers::update() {
  _timeClient.update();
}

String TimeHelpers::getCurrentLocalDateTime() {
  // update for good measure
  this->update();
  String day = String(_days_of_the_week[_timeClient.getDay()]);

  return day + " " + _timeClient.getFormattedTime();
}

std::chrono::time_point<std::chrono::system_clock> TimeHelpers::getClockTimeNow() {
  return std::chrono::system_clock::now();
}

double TimeHelpers::getElapsedTimeS(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end) {
  std::chrono::duration<double> elapsed_seconds = end - start;
  return elapsed_seconds.count();
}

String TimeHelpers::prettyFormatS(int seconds) {
  int minutes = seconds / 60;
  int hours = minutes / 60;
  int days = hours / 24;

  int rem_seconds = int(seconds % 60);
  int rem_minutes = int(minutes % 60);
  int rem_hours = int(hours % 60);
  int rem_days = int(days % 24);

  // days remaining?
  if (rem_days != 0) {
    return String(rem_days) + "d" + String(rem_hours) + "h " + String(rem_minutes) + "m " + String(rem_seconds) + "s";
  }

  // hours remaining?
  if (rem_hours != 0) {
    return String(rem_hours) + "h " + String(rem_minutes) + "m " + String(rem_seconds) + "s";
  }

  // don't show 0 mins/seconds
  if (rem_minutes == 0) {
    return String(rem_seconds) + "s";
  }

  if (rem_seconds == 0) {
    return String(rem_minutes) + "m ";
  }

  return String(rem_minutes) + "m " + String(rem_seconds) + "s";
}