#ifndef GPIO_H_
#define GPIO_H_

#include <Arduino.h>

class Gpio {
  public:
    Gpio(byte pin, byte pin_mode);
    int read();
    void write(byte val);
    void on();
    void off();
    bool isLow();
    bool isHigh();
    byte getPin();
    void readAndPrint();
  private:
    void init();
    byte Pin;
    byte PinMode;
};

#endif