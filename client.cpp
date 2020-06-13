#include "client/CApp.h"
#include <string>

int main(int argc, char const *argv[]) {
  std::string host("localhost");
  std::string port("7777");
  CApp theApp(host, port);
  theApp.OnExecute();
  return 0;
}
