#include "threadpool.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

struct ThreadPoolPrivate {
  mutable std::mutex mutex;
  mutable std::condition_variable condition;
  bool stop = false;

  std::vector<std::thread> threads;
  std::queue<std::function<void()>> tasks;
};

ThreadPool::ThreadPool(size_t thread_num)
    : d_(new ThreadPoolPrivate) {
  if (thread_num == 0) {
    thread_num = std::thread::hardware_concurrency();
    thread_num = (thread_num >= 8) ? (thread_num + 2) : (thread_num + 1);
  }

  std::unique_lock<std::mutex> lock(d_->mutex);
  d_->threads.reserve(thread_num);
  for (size_t i = 0; i < thread_num; ++i) {
    d_->threads.emplace_back([this] {
      while (true) {
        std::function<void(void)> task;
        {
          std::unique_lock<std::mutex> lock(d_->mutex);
          d_->condition.wait(lock,
                             [this] { return d_->stop || !d_->tasks.empty(); });
          if (d_->stop) {
            return;
          }
          task = std::move(d_->tasks.front());
          d_->tasks.pop();
        }
        task();
      }
    });
  }
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(d_->mutex);
    d_->stop = true;
  }
  d_->condition.notify_all();
  for (std::thread& thread : d_->threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

ThreadPool& ThreadPool::default_pool() {
  static ThreadPool pool;
  return pool;
}

void ThreadPool::AddTaskPrivate(std::function<void()>&& func) {
  {
    std::unique_lock<std::mutex> lock(d_->mutex);
    if (d_->stop) {
      return;
    }
    d_->tasks.emplace(func);
  }
  d_->condition.notify_one();
}
