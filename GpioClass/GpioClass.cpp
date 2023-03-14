#include "GpioClass.h"

Gpio::Gpio(byte pin, byte pin_mode) {
  this->Pin = pin;
  this->PinMode = pin_mode;

  this->init();
}

// private
void Gpio::init() {
  pinMode(this->Pin, this->PinMode);
}

// public
int Gpio::read() {
  return digitalRead(this->Pin);
}

void Gpio::write(byte val) {
  digitalWrite(this->Pin, val);
}

void Gpio::on() {
  this->write(HIGH);
}

void Gpio::off() {
  this->write(LOW);
}

bool Gpio::isLow() {
  return this->read() == LOW;
}

bool Gpio::isHigh() {
  return this->read() == HIGH;
}

byte Gpio::getPin() {
  return this->Pin;
}

void Gpio::readAndPrint() {
  Serial.print("GPIO pin ");
  Serial.print(this->Pin);
  Serial.print(" has value ");
  Serial.println(this->read());
}