/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:08:26 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/23 10:32:58 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>
class ThreadPool {
private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;
  std::mutex mutex;
  std::condition_variable cv;
  bool stop;

public:
  ThreadPool(std::size_t);
  ~ThreadPool();
  template <class F, class... Args>
  auto enqueue(F &&f, Args &&...args)
      -> std::future<typename std::result_of_t<F(Args...)>>;
};

inline ThreadPool::ThreadPool(std::size_t threads) : stop(false) {
  for (std::size_t i = 0; i < threads; ++i) {
    workers.emplace_back([this] {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(this->mutex);
          this->cv.wait(
              lock, [this]() { return this->stop or !this->tasks.empty(); });
          if (this->stop and this->tasks.empty()) {
            return;
          }
          task = std::move(this->tasks.front());
          this->tasks.pop();
        }
        task();
      }
    });
  }
}

inline ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(mutex);
    stop = true;
  }
  cv.notify_all();
  for (auto &worker : workers) {
    worker.join();
  }
}

template <class F, class... Args>
auto ThreadPool::enqueue(F &&f, Args &&...args)
    -> std::future<typename std::result_of_t<F(Args...)>> {
  using return_type =
      typename std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>;
  auto task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...));
  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(mutex);
    if (stop) {
      throw std::runtime_error("unqueue stopped threadpool error");
    }
    tasks.emplace([task]() { (*task)(); });
  }
  cv.notify_one();
}
