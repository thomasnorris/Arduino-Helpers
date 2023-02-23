#include "BlynkClasses.h"

// this must be in this .cpp file instead of the .h file
#include <BlynkSimpleEsp8266.h>

// debug flags
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

BlynkServer::BlynkServer(String ip_address, int port, String auth_token) {
  this->IP = ip_address;
  this->Port = port;
  this->AuthToken = auth_token;
}

void BlynkServer::configure() {
  IPAddress ip_address;
  ip_address.fromString(this->IP);

  Blynk.config(this->AuthToken.c_str(), ip_address, this->Port);
  this->disconnect();

  Serial.println("Blynk will connect to " + this->IP + " on port " + this->Port);
}

void BlynkServer::run() {
  Blynk.run();
}

bool BlynkServer::connected() {
  return Blynk.connected();
}

void BlynkServer::connect() {
  Blynk.connect();
}

void BlynkServer::disconnect() {
  Blynk.disconnect();
}

void BlynkServer::checkConnection() {
  if (!this->connected()) {
    Serial.println("Blynk is not connected");
    this->connect();
  }
}

// VirtualPin
VirtualPin::VirtualPin(int pin) {
  this->Pin = pin;
}

void VirtualPin::write(String val) {
  Blynk.virtualWrite(this->Pin, val);
}

void VirtualPin::write(int val) {
  Blynk.virtualWrite(this->Pin, val);
}

void VirtualPin::write(double val) {
  Blynk.virtualWrite(this->Pin, val);
}

void VirtualPin::on() {
  Blynk.virtualWrite(this->Pin, 1);
}

void VirtualPin::off() {
  Blynk.virtualWrite(this->Pin, 0);
}

// VirtualLed
VirtualLed::VirtualLed(int pin) {
  this->Pin = pin;
}

void VirtualLed::on() {
  WidgetLED led(this->Pin);
  led.on();
}

void VirtualLed::off() {
  WidgetLED led(this->Pin);
  led.off();
}