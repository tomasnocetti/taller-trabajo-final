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
protected:
  std::queue<T> queue;
  bool closed;
  std::mutex m;
  std::condition_variable cv;

public:
    BlockingQueue() : closed(false) {}
    explicit BlockingQueue(const T&) = delete;
    BlockingQueue& operator=(const T&) = delete;
    void push(T t) {
      std::unique_lock<std::mutex> lk(m);

      queue.push(std::move(t));
      cv.notify_all();
    }
    bool try_front(T& t) {
      std::unique_lock<std::mutex> lk(m);

      while (queue.empty()) {
        if (closed) {
          return false;
        }

        cv.wait(lk);
      }
      t = std::move(queue.front());
      return true;
    }
    bool try_pop() {
      std::unique_lock<std::mutex> lk(m);

      while (queue.empty()) {
        if (closed) {
          return false;
        }

        cv.wait(lk);
      }
      queue.pop();
      return true;
    }
    bool try_front_pop(T& t) {
      std::unique_lock<std::mutex> lk(m);

      while (queue.empty()) {
        if (closed) {
          return false;
        }

        cv.wait(lk);
      }
      t = std::move(queue.front());
      queue.pop();
      return true;
    }
    void close() {
      std::unique_lock<std::mutex> lk(m);
      closed = true;
      cv.notify_all();
    }
    ~BlockingQueue() {}
};

/**
 * @brief TDA FixedBlocking Queue it's a simple queue that will make a thread wait if
 * a try_pop() gets called (if not closed).
 * Push will notify all waiting threads. Only a a fixed size of items can be stored.
 * New items will push old items calling destructor.
 * Close will notify all waiting threads that the queue is closed.
 */
template<typename T>
class FixedBlockingQueue: public BlockingQueue<T> {
  private:
    size_t size;
  public:
    explicit FixedBlockingQueue(const T&) = delete;
    FixedBlockingQueue& operator=(const T&) = delete;
    explicit FixedBlockingQueue(size_t size) : size(size) {}
    void push(T t) {
      std::unique_lock<std::mutex> lk(this->m);

      if (size == 0) return;
      if (this->queue.size() >= size) {
        this->queue.pop();
      }
      this->queue.push(std::move(t));

      this->cv.notify_all();
    }
};

#endif
