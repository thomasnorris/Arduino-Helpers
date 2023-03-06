#ifndef EXCEPTION_HANDLER_H_
#define EXCEPTION_HANDLER_H_

#include <Arduino.h>

// somewhere else
extern void handleException(String origin, String message, String details = "");

class ExceptionHandler {
  public:
    ExceptionHandler();
    void handle(String origin);
    void wrap(void (*func)(), String origin);
  private:
};

#endif