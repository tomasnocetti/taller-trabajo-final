#ifndef SERVER_PROXY_WRITE_H
#define SERVER_PROXY_WRITE_H

#include "../../common/Thread.h"
#include "../../common/common_utils.h"
#include "ServerProxy.h"

using BlockingQueueWrite = BlockingQueue<InstructionData>;

class ServerProxy;

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

#endif
