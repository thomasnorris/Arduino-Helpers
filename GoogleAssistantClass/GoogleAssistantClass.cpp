#include "GoogleAssistantClass.h"

// reference: https://randomnerdtutorials.com/esp8266-nodemcu-http-get-post-arduino/

GAClient::GAClient(String url, String auth_header, String auth_token) {
  this->URL = url;
  this->AuthHeader = auth_header;
  this->AuthToken = auth_token;
}

void GAClient::send(String command) {
  WiFiClient client;
  HTTPClient http;

  String full_url = this->URL + "/" + command;
  if (http.begin(client, full_url.c_str())) {
    http.addHeader(this->AuthHeader, this->AuthToken);

    int httpCode = http.GET();
    Serial.println(httpCode);

    String payload = http.getString();
    Serial.println(payload);

    // free resources
    http.end();
  }
  else {
    Serial.println("There was an error sending a request to the Google Assistant.");
  }
}