#ifndef CLIENT_ACCEPTOR_H
#define CLIENT_ACCEPTOR_H

#include "../common/Thread.h"
#include "instructions/Instruction.h"
#include "ClientProxy.h"
#include "../common/common_socket.h"
#include <vector>
#include <memory>
#include <list>

class BlockinQueue;

class ClientAcceptor : public Thread{
  private:
    std::list<std::unique_ptr<ClientProxy>> clientProxies;
    InstructionBQ &instructionQueue;
    Socket bindedSocket;
  public:
    std::atomic<bool> running;
    explicit ClientAcceptor(InstructionBQ &instructionQueue);
    ~ClientAcceptor();
    ClientAcceptor(const ClientAcceptor&) = delete;
    ClientAcceptor& operator=(const ClientAcceptor&) = delete;
    void acceptClient();
    void run();
    void cleanCloseClients();
};

#endif
