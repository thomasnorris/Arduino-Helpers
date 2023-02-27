#ifndef GOOGLE_ASSISTANT_H_
#define GOOGLE_ASSISTANT_H_

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

class GAClient {
  public:
    GAClient(String url, String auth_header, String auth_token);
    void send(String command);
  private:
    String URL;
    String AuthHeader;
    String AuthToken;
};

#endif