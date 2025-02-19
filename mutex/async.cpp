#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

std::mutex m;
struct X {
  void foo(int i, const std::string &str) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << str << ' ' << i << '\n';
  }
  void bar(const std::string &str) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << str << '\n';
  }
  int operator()(int i) {
    std::lock_guard<std::mutex> lk(m);
    std::cout << i << '\n';
    return i + 10;
  }
};

template <typename RandomIt> int parallel_sum(RandomIt beg, RandomIt end) {
  auto len = end - beg;
  if (len < 1000)
    return std::accumulate(beg, end, 0);
  RandomIt mid = beg + len / 2;
  auto handle =
      std::async(std::launch::async, parallel_sum<RandomIt>, mid, end);
  int sum = parallel_sum(beg, mid);
  return sum + handle.get();
}

int main(int argc, char *argv[]) {
  std::vector<int> v(10000, 1);
  std::cout << "sum is " << parallel_sum(v.begin(), v.end()) << '\n';

  X x;
  auto a1 = std::async(std::launch::async, X(), 42);
  std::cout << a1.get() << '\n';

  auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
  std::this_thread::sleep_for(std::chrono::seconds(100));
  a2.wait();

  auto a3 = std::async(&X::foo, x, 43, "hello!");
  return 0;
}
