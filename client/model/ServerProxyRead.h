#ifndef SERVER_PROXY_READ_H
#define SERVER_PROXY_READ_H

#include "../../common/Thread.h"
#include "../../common/BlockingQueue.h"
#include "../../DataDefinitions.h"

using BlockingQueueRead = BlockingQueue<InstructionData>;

class ServerProxyRead : public Thread {
  public:
    explicit ServerProxyRead(BlockingQueueRead &readBQ);
    ~ServerProxyRead();
    ServerProxyRead(const ServerProxyRead&) = delete;
    ServerProxyRead& operator=(const ServerProxyRead&) = delete;
    void run();
  private:
    BlockingQueueRead &readBQ;
    bool continueReading;
};

#endif
