#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <condition_variable>
#include <queue>
#include <mutex>
#include "../DataDefinitions.h"

class BlockingQueue {
private:
    bool isClosed;
    std::mutex m;
    std::queue<InstructionData> queue;
    std::condition_variable cv;
public: 
    BlockingQueue();
    void push(InstructionData instruction);
    InstructionData pop();
    void close();
    ~BlockingQueue();
};

#endif
