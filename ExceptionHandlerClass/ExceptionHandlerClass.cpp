#include "ExceptionHandlerClass.h"

ExceptionHandler::ExceptionHandler() {
  // nothing
}

void ExceptionHandler::wrap(void (*func)(), String origin) {
  try {
    func();
  }
  catch(...) {
    this->handle(origin);
  }
}

// add additional types that could be caught here
void ExceptionHandler::handle(String origin) {
  try {
    throw;
  }
  catch (const std::exception& e) {
    handleException(origin, String(e.what()), "const std::exception&");
  }
  catch (const char* e) {
    handleException(origin, e, "const char*");
  }
  catch (...) {
    handleException(origin, "Unkown reason", "No details available");
  }
}