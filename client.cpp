#include "client/CApp.h"
#include <string>
#include <syslog.h>
#include <iostream>

#define EXIT_FAILURE 1

int main(int argc, char const *argv[]) {
  if(argc != 3) return EXIT_FAILURE;
  std::string host = argv[1];
  std::string port = argv[2];
  try {
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
