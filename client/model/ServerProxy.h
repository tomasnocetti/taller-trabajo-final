#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "../../DataDefinitions.h"
#include "../MapParser.h"
#include <string>
#include <vector>
#include "../../common/BlockingQueue.h"
#include "../../common/Thread.h"
#include "../../common/common_socket.h"

using BlockingQueueWrite = BlockingQueue<InstructionData>;
using BlockingQueueRead = BlockingQueue<InstructionData>;

class Socket;
class ServerProxy;

class ServerProxyRead : public Thread {
  public:
    explicit ServerProxyRead(BlockingQueueRead &readBQ);
    ~ServerProxyRead();
    ServerProxyRead(const ServerProxyRead&) = delete;
    ServerProxyRead& operator=(const ServerProxyRead&) = delete;
    void run();
  private:
    // BlockingQueueRead &readBQ;
    bool continueReading;
};

class ServerProxyWrite : public Thread {
  public:
    ServerProxyWrite(ServerProxy &server, BlockingQueueWrite &readBQ);
    ~ServerProxyWrite();
    ServerProxyWrite(const ServerProxyWrite&) = delete;
    ServerProxyWrite& operator=(const ServerProxyWrite&) = delete;
    void run();
    void close();
    void getInstruction(InstructionData &instruction);
    std::stringstream packInstruction(InstructionData &instruction);
    void sendInstruction(std::stringstream &buffer);

  private:
    bool continuePlaying;
    ServerProxy &server;
    BlockingQueueWrite &writeBQ;
};
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
    friend class ServerProxyWrite;
    bool authentificated;
    MapData map;
    MainPlayerData mainPlayer;
    std::vector<EnemyData> npcs;
    BlockingQueueWrite writeBQ;
    BlockingQueueRead readBQ;
    Socket socket;
    ServerProxyWrite serverProxyWrite;
    ServerProxyRead serverProxyRead;
};

#endif
