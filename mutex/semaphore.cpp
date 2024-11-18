#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

using namespace std::literals;

std::binary_semaphore smphSignal(0); // C++20

void ThreadProc() {
  smphSignal.acquire();
  std::cout << "[thread] got the signal" << std::endl;
  std::this_thread::sleep_for(3s);
  std::cout << "[thread] send the signal" << std::endl;
  smphSignal.release();
}

int main(int argc, char *argv[]) {
  std::jthread thrWorker(ThreadProc);
  std::cout << "[main] send the signal" << std::endl;
  smphSignal.release();
  std::this_thread::sleep_for(500ms);
  smphSignal.acquire();
  std::cout << "[main] got the signal" << std::endl;
  return 0;
}
