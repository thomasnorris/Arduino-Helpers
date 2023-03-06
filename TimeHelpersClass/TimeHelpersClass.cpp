#include "TimeHelpersClass.h"

namespace {
  const char DAYS_OF_THE_WEEK[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};

  // set NTPClient to EST time zone (UTC -5 Hours)
  long _utc_time_seconds = -5 * 3600;
  WiFiUDP _ntpUDP;
  NTPClient _timeClient(_ntpUDP, "north-america.pool.ntp.org", _utc_time_seconds);
}

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

String TimeHelpers::getCurrentLocalDateTime24hr() {
  this->update();
  String day_of_the_week = String(DAYS_OF_THE_WEEK[_timeClient.getDay()]);
  String time = this->getCurrentLocalTime24hr();

  return day_of_the_week + " " + time;
}

String TimeHelpers::getCurrentLocalDateTime12hr() {
  this->update();
  String day_of_the_week = String(DAYS_OF_THE_WEEK[_timeClient.getDay()]);
  String time = this->getCurrentLocalTime12hr();

  return day_of_the_week + " " + time;
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

String TimeHelpers::getCurrentLocalTime24hr() {
  this->update();
  return this->getFormattedTime();
}

String TimeHelpers::getCurrentLocalTime12hr() {
  this->update();
  String time_24hr = this->getFormattedTime();

  String am_pm = "AM";
  std::string time_24hr_cstr = time_24hr.c_str();
  std::string delimiter = String(":").c_str();

  // get the first chunk of the time
  std::stringstream ss;
  int hr;
  ss << time_24hr_cstr.substr(0, time_24hr_cstr.find(delimiter));
  ss >> hr;

  // convert into am/pm
  if (hr == 0) {
    hr = 12;
    am_pm = "AM";
  }

  if (hr >= 13) {
    hr -= 12;
    am_pm = "PM";
  }

  // pad the hour if needed
  String str_hr = String(hr);
  if (str_hr.length() == 1) {
    str_hr = "0" + str_hr;
  }

  // string back together and return
  std::string remaining_time_12hr = time_24hr_cstr.erase(0, time_24hr_cstr.find(delimiter) + delimiter.length());

  return String(str_hr.c_str()) + ":" + String(remaining_time_12hr.c_str()) + am_pm;
}

// private
String TimeHelpers::getFormattedTime() {
  this->update();
  return _timeClient.getFormattedTime();
}