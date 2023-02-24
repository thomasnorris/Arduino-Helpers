#include "BlynkClasses.h"

// this must be in this .cpp file instead of the .h file
#include <BlynkSimpleEsp8266.h>

// custom handling; requires defining function in main
BLYNK_WRITE_DEFAULT() {
  int pin = request.pin;
  String value = param.asStr();

  // somewhere else
  handleBlynkPinValueChange(pin, value);
}

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

  // disconnect right away so connection can be handled manually
  this->disconnect();
}

void BlynkServer::run() {
  Blynk.run();
}

bool BlynkServer::connected() {
  return Blynk.connected();
}

void BlynkServer::connect() {
  Blynk.connect();

  Serial.print("Blynk connected to ");
  Serial.print(this->IP);
  Serial.print(" on port ");
  Serial.println(this->Port);
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
  this->Value = -1;
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

void VirtualPin::write(unsigned long val) {
  Blynk.virtualWrite(this->Pin, val);
}

void VirtualPin::on() {
  Blynk.virtualWrite(this->Pin, 1);
}

void VirtualPin::off() {
  Blynk.virtualWrite(this->Pin, 0);
}

// only sets the Value property
void VirtualPin::set(String val) {
  this->Value = val;
}

String VirtualPin::read() {
  return this->Value;
}

bool VirtualPin::isOn() {
  return this->read().toInt() == 1;
}

bool VirtualPin::isOff() {
  return this->read().toInt() == 0;
}

// VirtualLed
VirtualLed::VirtualLed(int pin) {
  this->Pin = pin;
  this->Value = -1;
}

void VirtualLed::on() {
  WidgetLED led(this->Pin);
  led.on();
}

void VirtualLed::off() {
  WidgetLED led(this->Pin);
  led.off();
}

int VirtualLed::read() {
  WidgetLED led(this->Pin);
  return led.getValue();
}

bool VirtualLed::isOn() {
  return this->read() == 255;
}

bool VirtualLed::isOff() {
  return this->read() == 0;
}