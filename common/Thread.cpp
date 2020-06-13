#include "Thread.h"
#include <utility>

Thread::Thread() {}

Thread::~Thread() {
  if (thread.joinable())
    thread.join();
}

void Thread::start(){
  thread = std::thread(&Thread::run, this); // this->run(this)
}

void Thread::join(){
  if (thread.joinable())
    thread.join();
}

Thread::Thread(Thread&& other){
  this->thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other){
  this->thread = std::move(other.thread);
  return *this;
}
