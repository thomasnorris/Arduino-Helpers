#ifndef ARD_OTA_H_
#define ARD_OTA_H_

#include <Arduino.h>
#include <ArduinoOTA.h>

class OTAClient {
  public:
    OTAClient(String hostname = "", String password = "", int port = 8266);
    void begin();
    void handle();
  private:
    void init();
    String Hostname;
    String Password;
    int Port;
};

#endif