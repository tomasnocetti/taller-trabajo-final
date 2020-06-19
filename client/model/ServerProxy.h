#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "../../DataDefinitions.h"
#include "../MapParser.h"
#include <string>
#include <vector>

class ServerProxy {
  public:
    ServerProxy(std::string& host, std::string& port);
    ServerProxy(const ServerProxy&) = delete;
    ServerProxy& operator=(const ServerProxy&) = delete;
    ServerProxy&& operator=(ServerProxy&& other);
    void authentificate(std::string& alias);
    void init();
    void move(int xDir, int yDir);
    void moveNPC(int index, int xDir, int yDir);
    void attack(int xPos, int yPos);
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
