#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

int g_num = 0;
// std::mutex g_num_mutex;
std::mutex cout_mutex;
std::timed_mutex mutex;

// void slow_increment(int id) {
//   for (int i = 0; i < 3; ++i) {
//     g_num_mutex.lock();
//     ++g_num;
//     std::cout << id << " => " << g_num << "\n";
//     g_num_mutex.unlock();
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//   }
// }
using namespace std::chrono_literals;
void job(int id) {
  std::ostringstream stream;
  for (int i = 0; i < 3; ++i) {
    if (mutex.try_lock_for(200ms)) {
      stream << "success! ";
      std::this_thread::sleep_for(100ms);
      mutex.unlock();
    } else {
      stream << "failed! ";
    }
    std::this_thread::sleep_for(100ms);
  }
  std::lock_guard<std::mutex> lock{cout_mutex};
  std::cout << "[" << id << "] " << stream.str() << "\n";
}

int main(int argc, char *argv[]) {
  // std::thread t1{slow_increment, 0};
  // std::thread t2{slow_increment, 1};
  // t1.join();
  // t2.join();
  std::vector<std::thread> threads;
  for (int i = 0; i < 6; ++i) {
    threads.emplace_back(job, i);
  }
  for (auto &t : threads) {
    t.join();
  }
  return 0;
}
