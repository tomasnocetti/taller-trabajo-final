#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <condition_variable>
#include <queue>
#include <mutex>

/**
 * @brief TDA Blocking Queue it's a simple queue that will make a thread wait if
 * a try_pop() gets called (if not closed).
 * Push will notify all waiting threads.
 * Close will notify all waiting threads that the queue is closed.
 */
template<class T>
class BlockingQueue {
private:
    bool closed;
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;
public:
    BlockingQueue() : closed(false) {};
    BlockingQueue(const T&) = delete;
    BlockingQueue& operator=(const T&) = delete;
    void push(T t) {
      std::unique_lock<std::mutex> lk(m);

      queue.push(std::move(t));
      cv.notify_all();
    };
    bool try_pop(T& t) {
      std::unique_lock<std::mutex> lk(m);

      while (queue.empty()) {
        if (closed) {
          return true;
        }

        cv.wait(lk);
      }
      t = std::move(queue.front());
      queue.pop();
      return false;
    };
    void close() {
      std::unique_lock<std::mutex> lk(m);
      closed = true;
      cv.notify_all();
    };
    ~BlockingQueue() {};
};

#endif
