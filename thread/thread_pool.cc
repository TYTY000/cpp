/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.cc                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:34:38 by TYTY000           #+#    #+#             */
/*   Updated: 2024/08/15 17:26:56 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>
class ThreadPool {
   public:
    ThreadPool(size_t);
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ~ThreadPool();
    template <typename F, typename... Args>
    auto enqueue(F &&f, Args &&...args) -> std::future<decltype(f(args...))>;
    void stop();

   private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks{};
    std::condition_variable cv;
    std::mutex mutex;
    bool stopped;
};

ThreadPool::ThreadPool(size_t capacity) : stopped(false) {
    for (size_t i = 0; i < capacity; i++) {
        workers.emplace_back([this]() {
            for (;;) {
                std::function<void()> task{};
                {
                    std::unique_lock lock(mutex);
                    this->cv.wait(lock, [this]() {
                        return this->stopped or !tasks.empty();
                    });
                    if (this->stopped and tasks.empty()) {
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

ThreadPool::~ThreadPool() {
    stop();
    for (auto &worker : workers) {
        worker.join();
    }
}

template <typename F, typename... Args>
auto ThreadPool::enqueue(F &&f,
                         Args &&...args) -> std::future<decltype(f(args...))> {
    using return_type = decltype(f(args...));
    auto task = std::make_shared /* <std::packaged_task<return_type()>> */ (
        std::forward<F>(f), std::forward<Args...>(args...));
    // std::packaged_task<return_type()> task{std::forward<F>(f),
    // std::forward<Args...>(args...)};
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock lock(mutex);
        if (this->stopped) {
            throw std::runtime_error("enqueue on a stopped threadpool.");
        }
        tasks.emplace([task]() { (*task)(); });
        // tasks.emplace([task = std::move(task)]() mutable { task(); });
    }
    cv.notify_one();
    return res;
};

void ThreadPool::stop() {
    {
        std::unique_lock lock(mutex);
        stopped = true;
    }
    cv.notify_all();
}
