#ifndef QTDOCUMENTCN_TOOLS_THREAD_H
#define QTDOCUMENTCN_TOOLS_THREAD_H

#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <thread>

struct ThreadPoolPrivate;
class ThreadPool {
 public:
  explicit ThreadPool(size_t thread_num = 0);
  ~ThreadPool();

  static ThreadPool& default_pool();

  template <typename Func, typename... Args>
  auto AddTask(Func&& func, Args&&... args)
      -> std::future<typename std::result_of<Func(Args...)>::type>;

 private:
  void AddTaskPrivate(std::function<void(void)>&& func);
  std::unique_ptr<ThreadPoolPrivate> d_;
};

template <typename Func, typename... Args>
auto ThreadPool::AddTask(Func&& func, Args&&... args)
    -> std::future<typename std::result_of<Func(Args...)>::type> {
  using return_type = typename std::result_of<Func(Args...)>::type;
  auto task = std::make_shared<std::packaged_task<return_type()> >(
      std::bind(std::forward<Func>(func), std::forward<Args>(args)...));

  std::future<return_type> future = task->get_future();
  AddTaskPrivate([task] { (*task)(); });
  return future;
}

#endif  // QTDOCUMENTCN_TOOLS_THREAD_H
