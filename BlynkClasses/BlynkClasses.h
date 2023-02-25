#ifndef BLYNK_H_
#define BLYNK_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>

extern void handleBlynkPinValueChange(int pin, String value);

class BlynkServer {
  public:
    // server
    BlynkServer(String ip_address, int port, String auth_token);
    void configure();
    void connect();
    bool connected();
    void disconnect();
    void run();
    void checkConnection();
  private:
    String IP;
    String AuthToken;
    int Port;
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

#endif