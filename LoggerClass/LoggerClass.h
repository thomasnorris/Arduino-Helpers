#ifndef LOGGER_CLASS_H_
#define LOGGER_CLASS_H_

#include <Arduino.h>
#include "../MySQLConnectorClass/MySQLConnectorClass.h"

class LoggerClient {
  public:
    LoggerClient(int app_ID, String url, String username, String password, int port = 3306);
    void debug(String message, String details = "");
    void info(String message, String details = "");
    void warning(String message, String details = "");
    void error(String message, String details = "");
    void critical(String message, String details = "");
    void init(String message, String details = "");
  private:
    void sendLog(String message, String details, int log_type_ID);
    int AppID;
};

#endif