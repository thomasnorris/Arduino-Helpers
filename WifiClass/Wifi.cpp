#include "Wifi.h"

#define CONNECT_WAIT_DELAY_MS 250
#define MONITOR_DELAY_MS 1000

Wifi::Wifi(String ssid, String password, byte led_pin, byte led_pin_on_value) {
  this->SSID = ssid;
  this->Password = password;
  this->LED = new Led(led_pin, led_pin_on_value);
}

void Wifi::connect() {
  this->LED->off();
  WiFi.begin(this->SSID, this->Password);

  delay(CONNECT_WAIT_DELAY_MS);

  Serial.print("Connecting to Wifi network ");
  Serial.print(this->SSID);

  while (WiFi.status() != WL_CONNECTED) {
    this->LED->toggleOnOff(CONNECT_WAIT_DELAY_MS);
    Serial.print(".");
  }

  Serial.println("Connected!");

  this->printNetworkInfo();
  this->LED->on();
}

void Wifi::disconnect() {
  this->LED->off();
  WiFi.disconnect();
}

void Wifi::checkConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    this->disconnect();
    this->connect();
  }
}

void Wifi::printNetworkInfo() {
  Serial.print("SSID: ");
  Serial.println(this->SSID);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP().toString());
}