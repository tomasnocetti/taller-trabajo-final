#ifndef SERVER_PROXY_WRITE_H
#define SERVER_PROXY_WRITE_H

#include "../../common/Thread.h"
#include "../../common/BlockingQueue.h"
#include "../../DataDefinitions.h"
#include "../../common/common_utils.h"

using BlockingQueueWrite = BlockingQueue<InstructionData>;

class ServerProxyWrite : public Thread {
  public:
    ServerProxyWrite(BlockingQueueWrite &readBQ);
    ~ServerProxyWrite();
    ServerProxyWrite(const ServerProxyWrite&) = delete;
    ServerProxyWrite& operator=(const ServerProxyWrite&) = delete;
    void run();
    void close();
    void getInstruction(InstructionData &instruction);
    std::stringstream packInstruction(InstructionData &instruction);
    void sendInstruction(std::stringstream &buffer);

  private:
    BlockingQueueWrite &writeBQ;
    bool continuePlaying;
};

#endif
