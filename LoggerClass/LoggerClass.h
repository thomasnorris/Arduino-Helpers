#ifndef LOGGER_CLASS_H_
#define LOGGER_CLASS_H_

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

class LoggerClient {
  public:
    LoggerClient(String url, String auth_header, String auth_token, int app_ID);
    void debug(String message, String details = "");
    void info(String message, String details = "");
    void warning(String message, String details = "");
    void error(String message, String details = "");
    void critical(String message, String details = "");
    void init(String message, String details = "");
  private:
    String URL;
    String AuthHeader;
    String AuthToken;
    int AppID;
    void sendLog(String message, String details, int log_type);
    String buildJsonKVP(String key, String val);
};

#endif