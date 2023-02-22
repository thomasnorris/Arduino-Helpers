#include "Led.h"

Led::Led(byte pin, byte on_value) {
  this->Pin = pin;
  this->OnValue = on_value;

  this->init();
}

void Led::init() {
  pinMode(this->Pin, OUTPUT);
  this->off();
}

void Led::on() {
  digitalWrite(this->Pin, this->OnValue);
}

void Led::off() {
  digitalWrite(this->Pin, !this->OnValue);
}

void Led::toggleOnOff(int delay_ms, int after_delay_ms) {
  this->on();
  delay(delay_ms);
  this->off();

  if (after_delay_ms) {
    delay_ms = after_delay_ms;
  }

  delay(delay_ms);
}