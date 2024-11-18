#include <exception>
#include <iostream>
#include <mutex>
#include <ostream>
#include <thread>

std::once_flag flag1, flag2;

void once() {
  std::call_once(flag1, [] { std::cout << "call once\n"; });
}

void may_throw_function(bool do_throw) {
  if (do_throw) {
    std::cout << "throw by call_once\n";
    throw std::exception();
  }
  std::cout << "no throw\n";
}

void do_once(bool do_throw) {
  try {
    std::call_once(flag2, may_throw_function, do_throw);
  } catch (...) {
  }
}

int main(int argc, char *argv[]) {
  std::thread st1(once);
  std::thread st2(once);
  std::thread st3(once);
  std::thread st4(once);
  std::thread st5(once);
  st1.join();
  st2.join();
  st3.join();
  st4.join();
  st5.join();
  std::thread t1(do_once, true);
  std::thread t2(do_once, true);
  std::thread t3(do_once, true);
  std::thread t4(do_once, false);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  return 0;
}
