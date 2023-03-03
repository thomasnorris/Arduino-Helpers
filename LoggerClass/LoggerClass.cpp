#include "LoggerClass.h"

namespace {
  const int INVALID_TYPE_ID = 0;
  const int DEBUG_TYPE_ID = 1;
  const int INFO_TYPE_ID = 2;
  const int WARNING_TYPE_ID = 3;
  const int ERROR_TYPE_ID = 4;
  const int CRITICAL_TYPE_ID = 5;
  const int INIT_TYPE_ID = 6;

  const String LOG_SP = "AppLogs.SP_LogArduinoApp";

  MySQLConn* _sql;
}

// public
LoggerClient::LoggerClient(int app_ID, String url, String username, String password, int port) {
  _sql = new MySQLConn(url, username, password, port);
  this->AppID = app_ID;
}

void LoggerClient::debug(String message, String details) {
  this->sendLog(message, details, DEBUG_TYPE_ID);
}

void LoggerClient::info(String message, String details) {
  this->sendLog(message, details, INFO_TYPE_ID);
}

void LoggerClient::warning(String message, String details) {
  this->sendLog(message, details, WARNING_TYPE_ID);
}

void LoggerClient::error(String message, String details) {
  this->sendLog(message, details, ERROR_TYPE_ID);
}

void LoggerClient::critical(String message, String details) {
  this->sendLog(message, details, CRITICAL_TYPE_ID);
}

void LoggerClient::init(String message, String details) {
  this->sendLog(message, details, INIT_TYPE_ID);
}

// private
void LoggerClient::sendLog(String message, String details, int log_type_ID) {
  String escaped_message = "\"" + message + "\"";
  String escaped_details = "\"" + details + "\"";
  String query = "CALL " + LOG_SP + "(" + this->AppID + ", " + String(log_type_ID) + ", " + escaped_message + ", " + escaped_details + ");";

  _sql->upsert(query);
}