#ifndef CLIENT_ACCEPTOR_H
#define CLIENT_ACCEPTOR_H

#include "../common/BlockingQueue.h"
#include "../common/Thread.h"
#include "ServerProxy.h"
#include <vector>
#include <memory>
#include "ActivePlayers.h"

class BlockinQueue;

class ClientAcceptor : public Thread{
  private:
    std::vector<std::unique_ptr<ServerProxy>> serverProxies;
    InstructionDataBQ &instructionQueue;
    ActivePlayers &activePlayers;
  public:
    ClientAcceptor(InstructionDataBQ &instructionQueue, 
      ActivePlayers &activePlayers);
    ~ClientAcceptor();
    ClientAcceptor(const ClientAcceptor&) = delete;
    ClientAcceptor& operator=(const ClientAcceptor&) = delete;
    void acceptPlayer();
    void run();
};

#endif
