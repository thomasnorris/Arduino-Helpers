#include "GoogleAssistant.h"

// reference: https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/BasicHttpsClient/BasicHttpsClient.ino

GAClient::GAClient(String url, String auth_header, String auth_token) {
  this->URL = url;
  this->AuthHeader = auth_header;
  this->AuthToken = auth_token;
}

void GAClient::send(String command) {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  
  // disable https validation
  client->setInsecure();

  HTTPClient https;
  String fullUrl = this->URL + "/" + command;
  if (https.begin(*client, fullUrl)) {
    https.addHeader(this->AuthHeader, this->AuthToken);

    int httpCode = https.GET();
    Serial.println(httpCode);

    String payload = https.getString();
    Serial.println(payload);

    https.end();
  }
  else {
    Serial.println("There was an error sending the command.");
  }
}