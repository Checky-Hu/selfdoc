#ifndef THREAD_H_
#define THREAD_H_

#include <condition_variable>
#include <mutex>
#include <thread>

#include "fruit.h"

class Semaphore {
 public:
  Semaphore(int count = 0) : count_(count) {}
  ~Semaphore() {}
  void Signal();
  void Wait();

 private:
  std::condition_variable cv_;
  std::mutex mutex_;
  int count_;
};

class Thread {
 public:
  Thread(const std::string& name);
  ~Thread();
  void Consume(Fruit* fruit);

 private:
  enum State {kStart, kIdle, kRunning, kEnd};

  std::string name_;
  size_t current_value_;
  size_t consumed_;
  State state_;

  Semaphore semaphore_;
  std::thread thread_;
};

#endif
