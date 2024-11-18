#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void f1(int n) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "thread 1\n";
    ++n;
    std::this_thread::sleep_for(std::chrono::seconds(100));
  }
}

void f2(int &n) {
  for (int i = 0; i < 5; ++i) {
    std::cout << "thread 2\n";
    ++n;
    std::this_thread::sleep_for(std::chrono::seconds(100));
  }
}

class foo {
public:
  void bar() {
    for (int i = 0; i < 5; ++i) {
      std::cout << "thread 3\n";
      ++n;
      std::this_thread::sleep_for(std::chrono::seconds(100));
    }
  }
  int n = 0;
};
class baz {
public:
  void operator()() {
    for (int i = 0; i < 5; ++i) {
      std::cout << "thread 4\n";
      ++n;
      std::this_thread::sleep_for(std::chrono::seconds(100));
    }
  }
  int n = 0;
};

void slep(std::chrono::microseconds us) {
  auto start = std::chrono::high_resolution_clock::now();
  auto end = start + us;
  do {
    std::this_thread::yield();
  } while (std::chrono::high_resolution_clock::now() < end);
}
int main(int argc, char *argv[]) {
  std::thread t{[]() { std::cout << std::this_thread::get_id() << std::endl; }};
  t.join();
  int n = 0;
  foo f;
  baz b;
  std::thread t1;
  std::thread t2{f1, n + 1};
  std::thread t3{f2, std::ref(n)};
  std::thread t4{std::move(t3)};
  std::thread t5{&foo::bar, &f};
  std::thread t6{std::ref(b)};
  t2.join();
  t4.join();
  t5.join();
  t6.join();
  std::cout << "n = " << n << '\n';
  std::cout << "f.n = " << f.n << '\n';
  std::cout << "b.n = " << b.n << '\n';
  std::vector<std::thread> threads;
  for (size_t i = 0; i < 10; i++) {
    threads.emplace_back(
        []() { std::cout << std::this_thread::get_id() << std::endl; });
  }
  for (auto &t : threads) {
    t.join();
  }
  using namespace std::chrono_literals;
  // std::cout << "Hello waiter\n" << std::flush;
  // auto start = std::chrono::high_resolution_clock::now();
  // std::this_thread::sleep_for(2000ms);
  // auto end = std::chrono::high_resolution_clock::now();
  // std::chrono::duration<double, std::milli> elapsed = end - start;
  // std::cout << "waited " << elapsed.count() << "ms\n";
  std::cout << "------------------------------------\n";
  auto start1 = std::chrono::high_resolution_clock::now();
  slep(std::chrono::microseconds(100));
  auto elapsed1 = std::chrono::high_resolution_clock::now() - start1;
  std::cout
      << "waited for "
      << std::chrono::duration_cast<std::chrono::microseconds>(elapsed1).count()
      << " microseconds\n";
  return 0;
}
