#ifndef LED_H_
#define LED_H_

#include <Arduino.h>

class Led {
  public:
    Led(byte pin, byte on_value);
    void on();
    void off();
    void toggleOnOff(int delay_ms = 1000, int after_delay_ms = false);
  private:
    void init();
    byte Pin;
    byte OnValue;
};

#endif