#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <mutex>

/**
 * @brief TDA Queue it's a simple queue that will its safe.
 */
template<class T>
class Queue {
protected:
  std::queue<T> queue;
  bool closed;
  std::mutex m;

public:
    Queue() : closed(false) {}
    explicit Queue(const T&) = delete;
    Queue& operator=(const T&) = delete;
    void push(T t) {
      std::unique_lock<std::mutex> lk(m);

      queue.push(std::move(t));
    }
    bool try_front_pop(T& t) {
      std::unique_lock<std::mutex> lk(m);

      if (queue.empty() || closed) return false;

      t = std::move(queue.front());
      queue.pop();
      return true;
    }
    void close() {
      std::unique_lock<std::mutex> lk(m);
      closed = true;
    }
    int size(){
      std::unique_lock<std::mutex> lk(m);
      return queue.size();
    }
    ~Queue() {}
};

#endif
