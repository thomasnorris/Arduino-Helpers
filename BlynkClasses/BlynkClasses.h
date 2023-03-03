#ifndef BLYNK_H_
#define BLYNK_H_

/* Library Requirements */
// Blynk v1.0.0 (THIS VERSION!) See all releases here: https://github.com/blynkkk/blynk-library/releases
// ESP8266WiFi

#include <Arduino.h>
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
    void notify(String message);
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