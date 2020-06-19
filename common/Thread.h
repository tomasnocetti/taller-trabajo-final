#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread{
  public:
    Thread();
    virtual void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread() = 0;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other) = delete;
    Thread& operator=(Thread&& other);
  protected:
    std::thread thread;
};

#endif
