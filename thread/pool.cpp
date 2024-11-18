#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <iostream>
#include <thread>

void print(const std::string &message) { std::cout << message << std::endl; }

int main(int argc, char *argv[]) {
  boost::asio::thread_pool pool(4);

  boost::asio::post(pool, [] { print("hello first"); });
  boost::asio::post(pool, [] { print("hello second"); });
  boost::asio::post(pool, [] { print("hello third"); });
  boost::asio::post(pool, [] { print("hello forth"); });
  boost::asio::post(pool, [] { print("hello fifth"); });
  pool.join();
  std::cout << std::thread::hardware_concurrency() << std::endl;
  return 0;
}
