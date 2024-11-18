/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_list.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:03:43 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/03 20:13:26 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
template <typename T> class safe_list {
  mutable std::mutex m;
  std::condition_variable cv;
  std::queue<T> data_queue;

public:
  safe_list() {}
  void push(T new_value) {
    {
      std::lock_guard<std::mutex> lk{m};
      data_queue.push(new_value);
      std::cout << "push:" << new_value << std::endl;
    }
    cv.notify_one();
  }
  void pop(T &value) {
    std::unique_lock<std::mutex> lk{m};
    cv.wait(lk, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    std::cout << "pop:" << value << std::endl;
    data_queue.pop();
  }
  std::shared_ptr<T> pop() {
    std::unique_lock<std::mutex> lk{m};
    cv.wait(lk, [this] { return !data_queue.empty(); });
    std::shared_ptr<T> res{std::make_shared<T>(data_queue.front())};
    data_queue.pop();
    return res;
  }
  bool empty() const {
    std::lock_guard<std::mutex> lk{m};
    return data_queue.empty();
  }
};

void producer(safe_list<int> &q, int a) {
  for (int i = a; i < 10 + a; ++i) {
    q.push(i);
  }
}

void consumer(safe_list<int> &q, int a) {
  for (int i = a; i < 10 + a; ++i) {
    int value{};
    q.pop(value);
  }
}

int main(int argc, char *argv[]) {
  safe_list<int> q;
  std::thread consumer_1{consumer, std::ref(q), 0};
  std::thread consumer_2{consumer, std::ref(q), 0};
  std::thread producer_1{producer, std::ref(q), 10};
  std::thread producer_2{producer, std::ref(q), 10};
  consumer_1.join();
  producer_1.join();
  consumer_2.join();
  producer_2.join();
  return 0;
}
