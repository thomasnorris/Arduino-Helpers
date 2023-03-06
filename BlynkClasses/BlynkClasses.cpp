#include "BlynkClasses.h"

// requires setting up a Blynk Legacy server and connecting to it
// see legacy server setup here: https://github.com/Peterkn2001/blynk-server/releases
// server-0.41.17.jar used and works

// this must be in this .cpp file instead of the .h file
#include <BlynkSimpleEsp8266.h>

namespace {
  ExceptionHandler* _eh = new ExceptionHandler();
}

// custom handling; requires defining function in main
BLYNK_WRITE_DEFAULT() {
  try {
    int pin = request.pin;
    String value = param.asStr();

    // somewhere else
    handleBlynkPinValueChange(pin, value);
  }
  catch (...) {
    _eh->handle("BlynkClasses.cpp/BLYNK_WRITE_DEFAULT()");
  }
}

// debug flags
// #define BLYNK_PRINT Serial
// #define BLYNK_DEBUG

BlynkServer::BlynkServer(String ip_address, int port, String auth_token) {
  this->IP = ip_address;
  this->Port = port;
  this->AuthToken = auth_token;
}

void BlynkServer::configure() {
  try {
    IPAddress ip_address;
    ip_address.fromString(this->IP);

    Blynk.config(this->AuthToken.c_str(), ip_address, this->Port);

    // disconnect right away so connection can be handled manually
    this->disconnect();
  }
  catch (...) {
    _eh->handle("void BlynkServer::configure()");
  }
}

void BlynkServer::run() {
  try {
    Blynk.run();
  }
  catch (...) {
    _eh->handle("void BlynkServer::run()");
  }
}

bool BlynkServer::connected() {
  bool connected = false;
  try {
    return Blynk.connected();
  }
  catch (...) {
    _eh->handle("bool BlynkServer::connected()");
  }

  return connected;
}

void BlynkServer::connect() {
  try {
    Blynk.connect();

    Serial.print("Blynk connected to ");
    Serial.print(this->IP);
    Serial.print(" on port ");
    Serial.println(this->Port);
  }
  catch (...) {
    _eh->handle("void BlynkServer::connect()");
  }
}

void BlynkServer::disconnect() {
  try {
    Blynk.disconnect();
  }
  catch (...) {
    _eh->handle("void BlynkServer::disconnect()");
  }
}

void BlynkServer::checkConnection() {
  if (!this->connected()) {
    Serial.println("Blynk is not connected");
    this->connect();
  }
}

void BlynkServer::notify(String message) {
  Blynk.notify(message);
}

// VirtualPin
// triggers callback BLYNK_WRITE_DEFAULT() {} which should be defined
// to set the internal Value of each pin to whatever value it was changed to
// all write(...) functions here also set the internal pin value to avoid race conditions
VirtualPin::VirtualPin(int pin) {
  this->Pin = pin;
  this->Value = -1;
}

void VirtualPin::write(String val) {
  Blynk.virtualWrite(this->Pin, val);
  this->set(val);
}

void VirtualPin::write(int val) {
  Blynk.virtualWrite(this->Pin, val);
  this->set(String(val));
}

void VirtualPin::write(double val) {
  Blynk.virtualWrite(this->Pin, val);
  this->set(String(val));
}

void VirtualPin::write(unsigned long val) {
  Blynk.virtualWrite(this->Pin, val);
  this->set(String(val));
}

void VirtualPin::on() {
  Blynk.virtualWrite(this->Pin, 1);
  this->set("1");
}

void VirtualPin::off() {
  Blynk.virtualWrite(this->Pin, 0);
  this->set("0");
}

// only sets the Value property
// set when pin is written to via Blynk callback or from code
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

// VirtualTerminal
// avoids having the same thing printed over and over by keeping track of the
// last printed message and only printing it if it has changed
VirtualTerminal::VirtualTerminal(int pin) {
  this->Pin = pin;
  this->Value = "";
  this->MyTimeHelpers = nullptr;
}

VirtualTerminal::VirtualTerminal(int pin, TimeHelpers* th) {
  this->Pin = pin;
  this->Value = "";
  this->MyTimeHelpers = th;
}

void VirtualTerminal::debug(String string) {
  this->println(string, "[DEBUG]");
}

void VirtualTerminal::info(String string) {
  this->println(string, "[INFO]");
}

void VirtualTerminal::warning(String string) {
  this->println(string, "[WARN]");
}

void VirtualTerminal::error(String string) {
  this->println(string, "[ERR]");
}

void VirtualTerminal::critical(String string) {
  this->println(string, "[CRIT]");
}

void VirtualTerminal::init(String string) {
  this->println(string, "[INIT]");
}

void VirtualTerminal::print(String message, String prefix) {
  if (this->Value != message) {
    this->Value = message;

    message = this->buildMessage(message, prefix);

    WidgetTerminal term(this->Pin);
    term.print(message);
    term.flush();
  }
}

void VirtualTerminal::println(String message, String prefix) {
  if (this->Value != message) {
    this->Value = message;

    message = this->buildMessage(message, prefix);

    WidgetTerminal term(this->Pin);
    term.println(message);
    term.flush();
  }
}

void VirtualTerminal::clear() {
  WidgetTerminal term(this->Pin);
  term.clear();
}

// private
String VirtualTerminal::buildMessage(String message, String prefix) {
  String time = "";
  if (this->MyTimeHelpers != nullptr) {
    time = this->MyTimeHelpers->getCurrentLocalTime12hr() + ": ";
  }

  if (prefix != "") {
    return time + prefix + " " + message;
  }

  return time + message;
}