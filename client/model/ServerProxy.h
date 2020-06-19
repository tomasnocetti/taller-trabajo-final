#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include <string>
#include <vector>
#include <atomic>
#include "Response.h"
#include "../../DataDefinitions.h"
#include "../MapParser.h"
#include "../../common/BlockingQueue.h"
#include "../../common/Thread.h"
#include "../../common/common_socket.h"

using BlockingQueueWrite = BlockingQueue<InstructionData>;

class Socket;
class ServerProxy;

class ServerProxyRead : public Thread {
  public:
    explicit ServerProxyRead(ServerProxy &server);
    ServerProxyRead(const ServerProxyRead&) = delete;
    ServerProxyRead& operator=(const ServerProxyRead&) = delete;
    void run();
    void handleResponse();
  private:
    ServerProxy &server;
};

class ServerProxyWrite : public Thread {
  public:
    ServerProxyWrite(ServerProxy &server, BlockingQueueWrite &readBQ);
    ~ServerProxyWrite();
    ServerProxyWrite(const ServerProxyWrite&) = delete;
    ServerProxyWrite& operator=(const ServerProxyWrite&) = delete;
    void run();
    void getInstruction(InstructionData &instruction);
    std::stringstream packInstruction(InstructionData &instruction);
    void sendInstruction(std::stringstream &buffer);

  private:
    ServerProxy &server;
    BlockingQueueWrite &writeBQ;
};
class ServerProxy{
  public:
    ServerProxy(std::string& host, std::string& port);
    ~ServerProxy();
    ServerProxy(const ServerProxy&) = delete;
    ServerProxy& operator=(const ServerProxy&) = delete;
    ServerProxy&& operator=(ServerProxy&& other);
    void init();
    void update();
    bool isAuthenticated() const;
    /** Client ACTIONS */
    void authentificate(std::string& alias);
    void move(int xDir, int yDir);
    void moveNPC(int xDir, int yDir);
    /** Client GETERS */
    MapData getMapData() const;
    MainPlayerData getMainPlayerData() const;
    std::vector<EnemyData> getNPCData() const;
    void setMainPlayerData();
    void setMapData();
    void close();

  private:
    friend class ServerProxyWrite;
    friend class ServerProxyRead;
    bool authentificated;
    std::atomic<bool> running;
    MapData map;
    MainPlayerData mainPlayer;
    std::vector<EnemyData> npcs;
    BlockingQueueWrite writeBQ;
    ResponseQ readBQ;
    Socket socket;
    ServerProxyWrite serverProxyWrite;
    ServerProxyRead serverProxyRead;
    ResponseQ responseQ;
};

#endif
