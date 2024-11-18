#include <chrono>
#include <future>
#include <ios>
#include <iostream>
#include <ratio>

int fib(int n) {
  if (n < 3)
    return 1;
  else
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[]) {
  // std::promise<void> ready_promise, t1_promise, t2_promise;
  // std::shared_future<void> ready_future(ready_promise.get_future());

  // std::chrono::time_point<std::chrono::high_resolution_clock> start;

  // auto fun1 = [&, ready_future]() -> std::chrono::duration<double,
  // std::milli> {
  //   t1_promise.set_value();
  //   ready_future.wait();
  //   return std::chrono::high_resolution_clock::now() - start;
  // };

  // auto fun2 = [&, ready_future]() -> std::chrono::duration<double,
  // std::milli> {
  //   t2_promise.set_value();
  //   ready_future.wait();
  //   return std::chrono::high_resolution_clock::now() - start;
  // };

  // auto reault1 = std::async(std::launch::async, fun1);
  // auto reault2 = std::async(std::launch::async, fun2);

  // t1_promise.get_future().wait();
  // t2_promise.get_future().wait();

  // start = std::chrono::high_resolution_clock::now();
  // ready_promise.set_value();

  // std::cout << "thread 1 :" << reault1.get().count()
  //           << "thread 2 :" << reault2.get().count() << std::endl;

  std::shared_future<int> f1 =
      std::async(std::launch::async, []() { return fib(40); });
  std::shared_future<int> f2 =
      std::async(std::launch::async, []() { return fib(43); });
  std::cout << "waiting..." << std::endl;
  const auto start = std::chrono::system_clock::now();
  f1.wait();
  f2.wait();
  std::cout << std::boolalpha << f1.valid() << std::endl;
  const auto diff = std::chrono::system_clock::now() - start;
  std::cout << std::chrono::duration<double>(diff).count() << " seconds\n";
  std::cout << "f1: " << f1.get() << std::endl;
  std::cout << "f2: " << f2.get() << std::endl;
  return 0;
}
