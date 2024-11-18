#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last, std::promise<int> promise) {
  int sum = std::accumulate(first, last, 0);
  promise.set_value(sum);
}

using namespace std::chrono_literals;
void do_work(std::promise<void> barrier) {
  std::this_thread::sleep_for(1s);
  barrier.set_value();
}

int main(int argc, char *argv[]) {
  std::vector<int> numbers{1, 2, 3, 4, 5, 6};
  std::promise<int> accumulate_promise;
  std::future<int> accumulate_future = accumulate_promise.get_future();
  std::thread work_thread{accumulate, numbers.begin(), numbers.end(),
                          std::move(accumulate_promise)};
  std::cout << "result = " << accumulate_future.get() << std::endl;
  work_thread.join();
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::thread workload{do_work, std::move(barrier)};
  barrier_future.wait();
  workload.join();
  std::cout << "-------------------------\n";

  std::packaged_task<int()> task([]() { return 7; });
  std::future<int> f1 = task.get_future();
  std::thread{std::move(task)}.detach();

  std::future<int> f2 = std::async(std::launch::async, []() { return 8; });

  std::promise<int> p;
  std::future<int> f3 = p.get_future();
  std::thread{[&p] { p.set_value_at_thread_exit(9); }}.detach();

  std::cout << "waiting....\n";
  // f1.wait();
  // f2.wait();
  // f3.wait();
  std::cout << "done! => " << f1.get() << f2.get() << f3.get() << std::endl;

  // std::future<int> f4 = std::async(std::launch::async, []() {
  //   std::this_thread::sleep_for(3s);
  //   return 8;
  // });
  // std::cout << "waiting..." << std::endl;
  // std::future_status status;
  // do {
  //   status = f4.wait_for(1s);
  //   if (status == std::future_status::deferred) {
  //     std::cout << "deffered" << std::endl;
  //   } else if (status == std::future_status::timeout) {
  //     std::cout << "timeout" << std::endl;
  //   } else if (status == std::future_status::ready) {
  //     std::cout << "ready!" << std::endl;
  //   }
  // } while (status != std::future_status::ready);
  // std::cout << "result is " << f4.get() << '\n';
  std::chrono::system_clock::time_point two_seconds_passed =
      std::chrono::system_clock::now() + 2s;
  std::promise<int> p1;
  std::future<int> f5 = p1.get_future();
  std::thread{[](std::promise<int> p1) {
                std::this_thread::sleep_for(1s);
                p1.set_value_at_thread_exit(9);
              },
              std::move(p1)}
      .detach();
  std::promise<int> p2;
  std::future<int> f6 = p2.get_future();
  std::thread{[](std::promise<int> p6) {
                std::this_thread::sleep_for(5s);
                p6.set_value_at_thread_exit(8);
              },
              std::move(p2)}
      .detach();
  std::cout << "waiting for 2 seconds..." << std::endl;
  if (std::future_status::ready == f5.wait_until(two_seconds_passed)) {
    std::cout << "f5: " << f5.get() << std::endl;
  } else {
    std::cout << "f5 not complete!" << std::endl;
  }

  if (std::future_status::ready == f6.wait_until(two_seconds_passed)) {
    std::cout << "f6: " << f6.get() << std::endl;
  } else {
    std::cout << "f6 not complete!" << std::endl;
  }
  std::cout << "Done!" << std::endl;
  return 0;
}
