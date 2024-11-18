/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threadpool.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:42:23 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/26 16:38:33 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
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
  std::condition_variable condition;
  bool stop;

public:
  ThreadPool(size_t);
  template <class F, class... Args>
  auto enqueue(F &&f, Args &&...args)
      -> std::future<typename std::result_of_t<F(Args...)>>;
  ~ThreadPool();
};

inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
  for (size_t i = 0; i < threads; ++i) {
    workers.emplace_back([this] {
      for (;;) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(this->mutex);
          this->condition.wait(
              lock, [this] { return this->stop || !this->tasks.empty(); });
          if (this->stop && this->tasks.empty()) {
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
    if (stop)
      throw std::runtime_error("enqueue on stopped threadpool");
    tasks.emplace([task]() { (*task)(); });
  }
  condition.notify_one();
  return res;
}

inline ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(mutex);
    stop = true;
  }
  condition.notify_all();
  for (std::thread &worker : workers) {
    worker.join();
  }
}

void multiply(const int a, const int b) { const int ans = a * b; }

void multiply_output(int &out, const int a, const int b) { out = a * b; }

int multiply_return(const int a, const int b) {
  const int ans = a * b;
  return ans;
}

int main(int argc, char *argv[]) {
  ThreadPool pool(8);

  // std::cout << "--------------------------------" << std::endl;
  // for (int i = 1; i <= 3; ++i) {
  //   for (int j = 1; j <= 6; ++j) {
  //     pool.enqueue(multiply, i, j);
  //   }
  // }
  // std::cout << "submit success." << std::endl;

  // std::cout << "--------------------------------" << std::endl;
  // int output_ref{0};
  // auto future1 = pool.enqueue(multiply_output, std::ref(output_ref), 4, 5);
  // future1.get();
  // std::cout << "result of output is: " << output_ref << std::endl;

  // std::cout << "--------------------------------" << std::endl;
  // auto future2 = pool.enqueue(multiply_return, 4, 4);
  // int ans = future2.get();
  // std::cout << "result of return is: " << ans << std::endl;
  auto f3 = [](int i, double d) -> std::string { return "1"; };
  std::vector<std::future<std::string>> v;
  for (int i = 0; i < 8; ++i) {
    v.emplace_back(pool.enqueue(f3, 1, 3.0));
  }
  for (auto &f : v) {
    auto ans = f.get();
    std::cout << ans << " ";
  }
  return 0;
}
