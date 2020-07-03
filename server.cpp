#include <iostream>
#include <sstream>
#include <cassert>
#include <syslog.h>
#include "server/ServerRun.h"

int main() {
  try {
    char mapPath[] = "config.json";

    char port[] = "7777";
    serverRun(port, mapPath);
  } catch(const std::exception& e) {
    syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
    std::cout << "Error en el main thread: " << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch(...) {
    syslog(LOG_CRIT, "[Crit] Unknown Error!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
