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
  BlockingQueue &updateModel;
public:
  ClientAcceptor(BlockingQueue &updateModel);
  ~ClientAcceptor();
  void acceptPlayer();
  void run();
};

#endif
