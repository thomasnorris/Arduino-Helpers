#include "OTAClass.h"

OTAClient::OTAClient(String hostname, String password, int port) {
  this->Hostname = hostname;
  this->Password = password;
  this->Port = port;

  this->init();
}

void OTAClient::init() {
  ArduinoOTA.setPort(this->Port);

  if (this->Hostname != String("")) {
    ArduinoOTA.setHostname(this->Hostname.c_str());
  }

  if (this->Password != String("")) {
    ArduinoOTA.setPassword(this->Password.c_str());
  }

  // default functions taken from https://randomnerdtutorials.com/esp8266-ota-updates-with-arduino-ide-over-the-air/
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
}

void OTAClient::begin() {
  ArduinoOTA.begin();
}

void OTAClient::handle() {
  ArduinoOTA.handle();
}