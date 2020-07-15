#include "client/CApp.h"
#include <string>
#include <iostream>

#define EXIT_FAILURE 1
#define ARGUMENTS_ERROR "Para ejecutar el programa debe proveer el host "\
  "y el puerto del servidor. \n   * argentum-client <host> <port>"
#define LOG_PATH "/var/argentum/argentum-client.log"

int main(int argc, char const *argv[]) {
  try {
    FILE* f = freopen(LOG_PATH, "w", stderr);

    if (argc != 3) throw std::invalid_argument(ARGUMENTS_ERROR);
    std::string host = argv[1];
    std::string port = argv[2];
    CApp theApp(host, port);
    theApp.OnExecute();
    pclose(f);
  } catch(const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  } catch(const std::exception& e) {
    std::cout << "Ups, parece que hubo un problema. Para mas informacion " <<
    "puede chequear los logs del sistema ubicados en: \n  " <<
    LOG_PATH << std::endl;
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch(...) {
    std::cerr << "INVALID ERROR !" << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
