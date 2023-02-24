#include "LoggerClass.h"

// log types
#define INVALID 0
#define DEBUG 1
#define INFO 2
#define WARNING 3
#define ERROR 4
#define CRITICAL 5
#define INIT 6

// public
LoggerClient::LoggerClient(String url, String auth_header, String auth_token, int app_ID) {
  this->URL = url;
  this->AuthHeader = auth_header;
  this->AuthToken = auth_token;
  this->AppID = app_ID;
}

void LoggerClient::debug(String message, String details) {
  this->sendLog(message, details, DEBUG);
}

void LoggerClient::info(String message, String details) {
  this->sendLog(message, details, INFO);
}

void LoggerClient::warning(String message, String details) {
  this->sendLog(message, details, WARNING);
}

void LoggerClient::error(String message, String details) {
  this->sendLog(message, details, ERROR);
}

void LoggerClient::critical(String message, String details) {
  this->sendLog(message, details, CRITICAL);
}

void LoggerClient::init(String message, String details) {
  this->sendLog(message, details, INIT);
}

// private
void LoggerClient::sendLog(String message, String details, int log_type) {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

  // disable https validation
  client->setInsecure();

  HTTPClient https;
  if (https.begin(*client, this->URL)) {
    https.addHeader(this->AuthHeader, this->AuthToken);
    https.addHeader("Content-Type", "application/json");

    // body formatting reference: https://github.com/thomasnorris/REST-Logger/blob/master/config/config_template.json
    // json formating reference: https://randomnerdtutorials.com/esp32-http-get-post-arduino/
    String json = "{";
    json += this->buildJsonKVP("app_ID", String(this->AppID)) + ",";
    json += this->buildJsonKVP("log_type_ID", String(log_type)) + ",";
    json += this->buildJsonKVP("message", message);

    if (details != "") {
      json += "," + this->buildJsonKVP("details", details);
    }

    json += "}";

    int httpCode = https.POST(json);
    Serial.println(httpCode);

    String payload = https.getString();
    Serial.println(payload);

    // free resources
    https.end();
  }
  else {
    Serial.println("There was an error sending a request to the REST Logger.");
  }
}

String LoggerClient::buildJsonKVP(String key, String val) {
  return "\"" + key + "\":\"" + val + "\"";
}