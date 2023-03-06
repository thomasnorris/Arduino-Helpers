#include "WifiClass.h"

namespace {
  const int CONNECT_WAIT_DELAY_MS = 250;

  ExceptionHandler* _eh = new ExceptionHandler();
  Led* LED = nullptr;
}

WifiClient::WifiClient(String ssid, String password, byte led_pin, byte led_pin_on_value) {
  this->SSID = ssid;
  this->Password = password;

  LED = new Led(led_pin, led_pin_on_value);
}

void WifiClient::connect() {
  try {
    LED->off();
    WiFi.begin(this->SSID, this->Password);

    delay(CONNECT_WAIT_DELAY_MS);

    Serial.print("Connecting to Wifi network ");
    Serial.print(this->SSID);

    while (WiFi.status() != WL_CONNECTED) {
      LED->toggleOnOff(CONNECT_WAIT_DELAY_MS);
      Serial.print(".");
    }

    Serial.println("Connected!");

    this->printNetworkInfo();
    LED->on();
  }
  catch (...) {
    _eh->handle("void WifiClient::connect()");
  }
}

void WifiClient::disconnect() {
  try {
    LED->off();
    WiFi.disconnect();
  }
  catch (...) {
    _eh->handle("void WifiClient::disconnect()");
  }
}

void WifiClient::checkConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    this->disconnect();
    this->connect();
  }
}

void WifiClient::printNetworkInfo() {
  Serial.print("SSID: ");
  Serial.println(this->SSID);
  Serial.print("IP Address: ");
  Serial.println(this->getIPAddress());
}

String WifiClient::getIPAddress() {
  return WiFi.localIP().toString();
}