#include <iostream>
#include <sstream>
#include <cassert>
#include <syslog.h>
#include "server/ServerRun.h"

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) return EXIT_FAILURE;
    char* mapPath = argv[1];
    //char mapPath[] = "/etc/argentum/config.json";
    //char port[] = "7777";
    char* port = argv[2];
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
