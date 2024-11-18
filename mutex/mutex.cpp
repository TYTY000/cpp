#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

std::map<std::string, std::string> pages;
std::mutex pages_mutex;

void save_page(const std::string &url) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::string result = "fake content";
  std::lock_guard<std::mutex> guard(pages_mutex);
  pages[url] = result;
}

int main(int argc, char *argv[]) {
  std::thread t1{save_page, "http://1"};
  std::thread t2{save_page, "http://2"};
  t1.join();
  t2.join();
  for (const auto &pair : pages) {
    std::cout << pair.first << " => " << pair.second << '\n';
  }
  return 0;
}
