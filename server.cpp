#include <iostream>
#include "server/ServerRun.h"

#define ARGUMENTS_ERROR "Para ejecutar el programa debe proveer el archivo "\
  "de configuracion y el puerto del servidor. \n"\
  "   * argentum-server <path/to/config> <port>"
#define LOG_PATH "/var/argentum/argentum-server.log"

int main(int argc, char* argv[]) {
  try {
    freopen(LOG_PATH, "w", stderr);
    if (argc != 3) throw std::invalid_argument(ARGUMENTS_ERROR);

    char* mapPath = argv[1];
    char* port = argv[2];
    serverRun(port, mapPath);
  } catch(const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  } catch(const std::exception& e) {
    std::cout << "Ups, parece que hubo un problema. Para mas informacion " <<
    "puede chequear los logs del sistema ubicados en: \n  " << LOG_PATH << std::endl;
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch(...) {
    std::cerr << "INVALID ERROR !" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
