#ifndef WIFI_H_
#define WIFI_H_

/* Library Requirements */
// https://github.com/arduino-libraries/NTPClient
// ESP8266WiFi

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wl_definitions.h"
#include "../LedClass/LedClass.h"

class WifiClient {
  public:
    WifiClient(String ssid, String password, byte led_pin, byte led_pin_on_value);
    void connect();
    void disconnect();
    void checkConnection();
    void printNetworkInfo();
    String getIPAddress();
  private:
    String SSID;
    String Password;
    Led* LED;
};

#endif