#ifndef CLIENT_ACCEPTOR_H
#define CLIENT_ACCEPTOR_H

#include "../common/BlockingQueue.h"
#include "../common/Thread.h"
#include "ClientProxy.h"
#include <vector>
#include <memory>

class BlockinQueue;

class ClientAcceptor : public Thread{
  private:
    std::vector<std::unique_ptr<ClientProxy>> serverProxies;
    InstructionDataBQ &instructionQueue;
  public:
    explicit ClientAcceptor(InstructionDataBQ &instructionQueue);
    ~ClientAcceptor();
    ClientAcceptor(const ClientAcceptor&) = delete;
    ClientAcceptor& operator=(const ClientAcceptor&) = delete;
    void acceptPlayer();
    void run();
};

#endif
