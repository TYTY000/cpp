/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packaged.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:23:42 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/03 20:23:42 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
// #include <functional>
#include <future>
#include <iostream>
#include <thread>
template <typename R, typename... Ts, typename... Args>
  requires std::invocable<std::packaged_task<R(Ts...)> &, Args...>
void async_task(std::packaged_task<R(Ts...)> &task, Args &&...args) {
  // todo..
  task(std::forward<Args>(args)...);
}

int main() {
  std::packaged_task<int(int, int)> task([](int a, int b) { return a + b; });

  int value = 50;
  std::future<int> future = task.get_future();
  // 创建一个线程来执行异步任务
  std::thread t{[&] { async_task(task, value, value); }};
  std::cout << future.get() << '\n';
  t.join();
}

// int f(int x, int y) {
//   std::cout << std::this_thread::get_id() << std::endl;
//   return std::pow(x, y);
// }

// void task_lambda() {
//   std::packaged_task<int(int, int)> task(f);

//   std::future<int> result = task.get_future();
//   task(2, 9);
//   std::cout << "task_lambda:\t" << result.get() << std::endl;
// }

// void task_bind() {
//   std::packaged_task<int()> task{std::bind(f, 2, 11)};
//   std::future<int> result = task.get_future();
//   task();
//   std::cout << "task_bind:\t" << result.get() << std::endl;
// }

// void task_thread() {
//   std::packaged_task<int(int, int)> task{f};
//   std::future<int> result = task.get_future();
//   std::thread t{std::move(task), 2, 10};
//   t.join();
//   std::cout << "task_thread:\t" << result.get() << std::endl;
// }

// int main(int argc, char *argv[]) {
//   std::cout << "main thread: " << std::this_thread::get_id() << std::endl;
//   std::cout << "---------------------------" << std::endl;
//   task_thread(); // new thread
//   std::cout << "---------------------------" << std::endl;
//   task_bind(); // no new thread
//   std::cout << "---------------------------" << std::endl;
//   task_lambda(); // no new thread
//   return 0;
// }
