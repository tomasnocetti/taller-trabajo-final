#ifndef CLIENT_ACCEPTOR_H
#define CLIENT_ACCEPTOR_H

#include "BlockingQueue.h"
#include "ServerProxy.h"
#include <vector>
#include <memory>

class BlockinQueue;

class ClientAcceptor{
private:
  std::vector<std::unique_ptr<ServerProxy>> serverProxies;
  InstructionDataBQ &updateModel;
public:
  explicit ClientAcceptor(InstructionDataBQ &updateModel);
  ~ClientAcceptor();
  void acceptPlayer();
  void run();
};

#endif
