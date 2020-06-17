#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "../../DataDefinitions.h"
#include "../MapParser.h"
#include <string>
#include <vector>
#include "../../common/BlockingQueue.h"
#include "ServerProxyWrite.h"
#include "ServerProxyRead.h"

using BlockingQueueWrite = BlockingQueue<InstructionData>;
using BlockingQueueRead = BlockingQueue<InstructionData>;

class ServerProxy{
  public:
    ServerProxy(std::string& host, std::string& port);
    ServerProxy(const ServerProxy&) = delete;
    ServerProxy& operator=(const ServerProxy&) = delete;
    ServerProxy&& operator=(ServerProxy&& other);
    void authentificate(std::string& alias);
    void init();
    void move(int xDir, int yDir);
    void moveNPC(int xDir, int yDir);
    bool isAuthenticated() const;
    MapData getMapData() const;
    MainPlayerData getMainPlayerData() const;
    std::vector<EnemyData> getNPCData() const;
    void close();

  private:
    bool authentificated;
    MapData map;
    MainPlayerData mainPlayer;
    std::vector<EnemyData> npcs;
    BlockingQueueWrite writeBQ;
    BlockingQueueRead readBQ;
    ServerProxyWrite serverProxyWrite;
    ServerProxyRead serverProxyRead;

};

#endif
