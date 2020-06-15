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
    void walk(int x, int y);
    void walkNPC(int x, int y);
    MapData getMapData() const;
    MainPlayerData getMainPlayerData() const;
    std::vector<EnemyData> getNPCData() const;
    void a(int a);
  private:
    MapData map;
    MainPlayerData mainPlayer;
    std::vector<EnemyData> npcs;
};

#endif
