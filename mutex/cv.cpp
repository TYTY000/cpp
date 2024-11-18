/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cv.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:37:46 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/03 18:39:14 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;
std::mutex mtx;
std::condition_variable cv;
bool arrived = false;

void waitForArrival() {
  std::unique_lock<std::mutex> lck(mtx);
  cv.wait(lck, [] { return arrived; }); // 等待 arrived 变为 true
  std::cout << "到达目的地，可以下车了！" << std::endl;
}

void simulateArrival() {
  std::this_thread::sleep_for(
      // std::chrono::seconds(5)); // 模拟地铁到站，假设5秒后到达目的地
      5s);
  {
    std::lock_guard<std::mutex> lck(mtx);
    arrived = true; // 设置条件变量为 true，表示到达目的地
  }
  cv.notify_one(); // 通知等待的线程
}

int main() {
  std::thread t1(waitForArrival);
  std::thread t2(simulateArrival);

  t1.join();
  t2.join();
}

// std::mutex m;
// std::condition_variable cv;
// // std::string data;
// bool ready = false;
// // bool processed{false};

// // void worker_thread() {
// //   std::unique_lock<std::mutex> lk(m);
// //   cv.wait(lk, [] { return ready; });

// //   std::cout << "worker processing\n";
// //   data += " after processing";
// //   processed = true;
// //   std::cout << "data processing compoleted.\n";
// //   lk.unlock();
// //   cv.notify_one();
// // }

// void print_id(int id) {
//   std::unique_lock<std::mutex> lk(m);
//   cv.wait(lk, []() { return ready == true; });
//   std::cout << "thread " << id << std::endl;
// }

// void go() {
//   std::lock_guard<std::mutex> lk(m);
//   ready = true;
//   cv.notify_all();
// }

// int main(int argc, char *argv[]) {
//   // std::thread worker{worker_thread};
//   // data = "Example data";
//   // {
//   //   std::lock_guard<std::mutex> lk(m);
//   //   ready = true;
//   //   std::cout << "main thread ready for processing." << std::endl;
//   // }
//   // cv.notify_one();
//   // {
//   //   std::unique_lock<std::mutex> lk(m);
//   //   cv.wait(lk, [] { return processed; });
//   // }
//   // std::cout << "back in main, data = " << data << std::endl;
//   // worker.join();
//   std::thread threads[10];
//   for (int i = 0; i < 10; ++i) {
//     threads[i] = std::thread{print_id, i};
//   }
//   std::cout << "ready to race..." << std::endl;
//   go();
//   for (auto &t : threads) {
//     t.join();
//   }
//   return 0;
// }
