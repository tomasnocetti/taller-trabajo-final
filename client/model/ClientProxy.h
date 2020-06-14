#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "../../DataDefinitions.h"
#include "../MapParser.h"
#include <string>
//#include <iostream>

class ClientProxy {
  public:
    ClientProxy(std::string& host, std::string& port);
    ClientProxy(const ClientProxy&) = delete;
    ClientProxy& operator=(const ClientProxy&) = delete;
    ClientProxy&& operator=(ClientProxy&& other);
    void authentificate(std::string& alias);
    void init();
    MapData getMapData() const {
      return map;
    }
  private:
    MapData map;
};

#endif
