#include "thread.h"

#include <iostream>

void Semaphore::Wait() {
  std::unique_lock<std::mutex> lock(mutex_);
  if (count_ == 0)
    cv_.wait(lock);
  count_--;
}

void Semaphore::Signal() {
  {
    std::unique_lock<std::mutex> lock(mutex_);
    count_++;
  }
  cv_.notify_one();
}

Thread::Thread(const std::string& name)
  : name_(name),
    current_value_(0),
    consumed_(0),
    state_(kStart),
    semaphore_(0) {
  thread_ = std::thread([this]() -> void {
    while (true) {
      switch (state_) {
        case kStart:
	  state_ = kIdle;
	  semaphore_.Signal();
	  break;
        case kIdle:
	  std::this_thread::sleep_for(std::chrono::milliseconds(400));
	  break;
	case kRunning:
          std::cout << "Thread " << name_
	    << " consume " << current_value_ << std::endl;
	  consumed_ += current_value_;
	  current_value_ = 0;
	  state_ = kIdle;
	  semaphore_.Signal();
	  break;
	case kEnd:
          std::cout << "Delete Thread " << name_
	    << " consume " << consumed_ << std::endl;
	  return;
      }
    }
  });
  semaphore_.Wait();
  std::cout << "New Thread " << name_ << std::endl;
}

Thread::~Thread() {
  state_ = kEnd;
  thread_.join();
}

void Thread::Consume(Fruit* fruit) {
  current_value_ = fruit->value();
  state_ = kRunning;
  semaphore_.Wait();
  delete fruit;
}
