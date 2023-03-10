#ifndef BLYNK_H_
#define BLYNK_H_

/* Library Requirements */
// Blynk v1.0.0 (THIS VERSION!) See all releases here: https://github.com/blynkkk/blynk-library/releases
// ESP8266WiFi

#include <Arduino.h>
#include <IPAddress.h>
#include "../TimeHelpersClass/TimeHelpersClass.h"
#include "../ExceptionHandlerClass/ExceptionHandlerClass.h"

extern void handleBlynkPinValueChange(int pin, String value);

class BlynkServer {
  public:
    BlynkServer(String ip_address, int port, String auth_token);
    void configure();
    void connect();
    bool connected();
    void disconnect();
    void run();
    void checkConnection();
    void notify(String message, bool priority = false);
    void notifySetEnabled(bool enabled = true);
    bool notifyGetEnabled();
    void notifyToggleEnabled();
  private:
    String IP;
    String AuthToken;
    int Port;
    bool NotifyEnabled;
};

class VirtualPin {
  public:
    VirtualPin(int pin);
    void on();
    void off();
    void write(String val);
    void write(int val);
    void write(double val);
    void write(unsigned long val);
    String read();
    void set(String val);
    bool isOn();
    bool isOff();
  private:
    int Pin;
    String Value;
};

class VirtualLed {
  public:
    VirtualLed(int pin);
    void on();
    void off();
    int read();
    bool isOn();
    bool isOff();
  private:
    int Pin;
};

class VirtualTerminal {
  public:
    VirtualTerminal(int pin);
    VirtualTerminal(int pin, TimeHelpers* th);
    void debug(String string);
    void info(String string);
    void warning(String string);
    void error(String string);
    void critical(String string);
    void init(String string);
    void help(String string);
    void emptyln();
    void print(String message = "", String prefix = "", bool with_time = true);
    void println(String message = "", String prefix = "", bool with_time = true);
    void clear();
  private:
    int Pin;
    String Value;
    TimeHelpers* MyTimeHelpers;
    String buildMessage(String message, String prefix = "", bool with_time = true);
};

#endif