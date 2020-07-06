#include <iostream>
#include <syslog.h>
#include "server/ServerRun.h"

#define ARGUMENTS_ERROR "Para ejecutar el programa debe proveer el archivo "\
  "de configuracion y el puerto del servidor. \n"\
  "   * argentum-server <path/to/config> <port>"

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) throw std::invalid_argument(ARGUMENTS_ERROR);
    char* mapPath = argv[1];
    char* port = argv[2];
    serverRun(port, mapPath);
  } catch(const std::exception& e) {
    syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch(...) {
    syslog(LOG_CRIT, "[Crit] Unknown Error!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
