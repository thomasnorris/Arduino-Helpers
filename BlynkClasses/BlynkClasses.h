#ifndef BLYNK_H_
#define BLYNK_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>

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
  private:
    int Pin;
};

class VirtualLed {
  public:
    VirtualLed(int pin);
    void on();
    void off();
  private:
    int Pin;
};

#endif