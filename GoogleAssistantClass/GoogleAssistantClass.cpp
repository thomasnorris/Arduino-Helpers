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

      int httpCode = http.GET();
      Serial.println(httpCode);

      String payload = http.getString();
      Serial.println(payload);

      // free resources
      http.end();
    }
    else {
      throw "Could not begin request";
    }
  }
  catch (...) {
    _eh->handle("void GAClient::send(String command)");
  }
}