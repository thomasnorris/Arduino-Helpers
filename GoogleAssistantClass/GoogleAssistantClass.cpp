#include "GoogleAssistantClass.h"

// reference: https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/

namespace {
  ExceptionHandler* _eh = new ExceptionHandler();
}

GAClient::GAClient(String url, String auth_header, String auth_token) {
  this->URL = url;
  this->AuthHeader = auth_header;
  this->AuthToken = auth_token;
}

void GAClient::send(String command) {
  try {
    WiFiClient client;
    HTTPClient http;

    String full_url = this->URL + "/" + command;
    full_url.replace(" ", "%20");
    if (http.begin(client, full_url)) {
      http.addHeader(this->AuthHeader, this->AuthToken);

      Serial.println("Sending " + full_url);

      int http_code = http.GET();
      String payload = http.getString();

      // free resources
      http.end();

      // all is good
      if (http_code != HTTP_CODE_OK) {
        throw "ErrorCode: " + String(http_code) + ", Payload: " + payload + ", URL: " + full_url;
      }
    }
    else {
      throw "Could not begin request";
    }
  }
  catch (...) {
    _eh->handle("void GAClient::send(String command)");
  }
}