#include <future>
#include <iostream>
#include <thread>

void mythread(std::promise<int> &pro, int n) {
  int t{};
  for (int i = 0; i < n; ++i) {
    t += i;
  }
  pro.set_value(t);
}

int main(int argc, char *argv[]) {
  std::promise<int> pro;
  std::thread t{mythread, std::ref(pro), 10};
  t.join();
  std::future<int> f = pro.get_future();
  auto result = f.get();
  std::cout << result << std::endl;
  return 0;
}
