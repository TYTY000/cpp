#include <iostream>
#include <mutex>
#include <thread>
#include <tuple>
#include <vector>

template <class... Mutexes> class scoped_lock {
private:
  std::tuple<Mutexes &...> MyMutexes;

public:
  explicit scoped_lock(Mutexes &...Mtxes) : MyMutexes(Mtxes...) {
    std::lock(Mtxes...);
  }
  explicit scoped_lock(std::adopt_lock_t, Mutexes &...Mtxes)
      : MyMutexes(Mtxes...) {}
  ~scoped_lock() noexcept {
    std::apply([](Mutexes &...Mtxes) { (..., Mtxes.unlock()); }, MyMutexes);
  }
  scoped_lock(const scoped_lock &) = delete;
  scoped_lock &operator=(const scoped_lock &) = delete;
};

void func() {
  static std::mutex m1, m2;
  scoped_lock lock(m1, m2);
  std::cout << "message\t\n" << std::endl;
}

int main(int argc, char *argv[]) {
  std::vector<std::thread> v;
  for (int i = 0; i < 10; i++) {
    v.emplace_back(func);
  }
  for (auto &t : v) {
    t.join();
  }
  return 0;
}
