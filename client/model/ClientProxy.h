#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "../../DataDefinitions.h"
#include "../MapParser.h"
#include <string>
#include <vector>

class ClientProxy {
  public:
    ClientProxy(std::string& host, std::string& port);
    ClientProxy(const ClientProxy&) = delete;
    ClientProxy& operator=(const ClientProxy&) = delete;
    ClientProxy&& operator=(ClientProxy&& other);
    void authentificate(std::string& alias);
    void init();
    bool isAuthenticated() const;
    MapData getMapData() const;
    MainPlayerData getMainPlayerData() const;
    std::vector<EnemyData> getNPCData() const;
  private:
    bool authentificated;
    MapData map;
    MainPlayerData mainPlayer;
    std::vector<EnemyData> npcs;
};

#endif
