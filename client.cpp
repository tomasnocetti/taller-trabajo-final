#include "client/CApp.h"
#include <string>
#include <syslog.h>
#include <iostream>

#define EXIT_FAILURE 1
#define ARGUMENTS_ERROR "Para ejecutar el programa debe proveer el host "\
  "y el puerto del servidor. \n   * argentum-client <host> <port>"

int main(int argc, char const *argv[]) {
  try {
    if (argc != 3) throw std::invalid_argument(ARGUMENTS_ERROR);
    std::string host = argv[1];
    std::string port = argv[2];
    CApp theApp(host, port);
    theApp.OnExecute();
  } catch(const std::exception& e) {
    syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch(...) {
    syslog(LOG_CRIT, "[Crit] Unknown Error!");
    return EXIT_FAILURE;
  }
  return 0;
}
