#ifndef CLIENT_ACCEPTOR_H
#define CLIENT_ACCEPTOR_H

#include "../common/Thread.h"
#include "instructions/Instruction.h"
#include "ClientProxy.h"
#include <vector>
#include <memory>

class BlockinQueue;

class ClientAcceptor : public Thread{
  private:
    std::vector<std::unique_ptr<ClientProxy>> serverProxies;
    InstructionBQ &instructionQueue;
  public:
    explicit ClientAcceptor(InstructionBQ &instructionQueue);
    ~ClientAcceptor();
    ClientAcceptor(const ClientAcceptor&) = delete;
    ClientAcceptor& operator=(const ClientAcceptor&) = delete;
    void acceptClient();
    void run();
};

#endif
