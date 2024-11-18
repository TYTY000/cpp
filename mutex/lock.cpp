#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

struct X {
  X(std::string id) : id(id) {}
  std::string id;
  std::vector<std::string> lunch_partners;
  std::mutex m;
  std::string output() const {
    std::string ret = "Employee " + id + " has lunch partners: ";
    for (const auto &partner : lunch_partners) {
      ret += partner + " ";
    }
    ret += "\n";
    return ret;
  }
};

void send_mail(X &, X &) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void assign_lunch_partner(X &x1, X &x2) {
  static std::mutex io_mutex;
  {
    std::lock_guard<std::mutex> lk(io_mutex);
    std::cout << x1.id << " and " << x2.id << " are waiting for locks"
              << std::endl;
  }
  {
    // std::lock(x1.m, x2.m);
    // std::lock_guard<std::mutex> lk1(x1.m, std::adopt_lock);
    // std::lock_guard<std::mutex> lk2(x2.m, std::adopt_lock);

    // std::scoped_lock lock(x1.m, x2.m);

    std::unique_lock<std::mutex> lk1(x1.m, std::defer_lock);
    std::unique_lock<std::mutex> lk2(x2.m, std::defer_lock);
    std::lock(lk1, lk2);
    {
      std::lock_guard<std::mutex> lk(io_mutex);
      std::cout << x1.id << " and " << x2.id << " got locks" << std::endl;
    }
    x1.lunch_partners.push_back(x2.id);
    x2.lunch_partners.push_back(x1.id);
  }
  send_mail(x1, x2);
  send_mail(x2, x1);
}

int main(int argc, char *argv[]) {
  X alice{"alice"}, bob{"bob"}, charlie{"charlie"}, dave{"dave"};
  std::vector<std::thread> threads;
  threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
  threads.emplace_back(assign_lunch_partner, std::ref(charlie), std::ref(bob));
  threads.emplace_back(assign_lunch_partner, std::ref(charlie),
                       std::ref(alice));
  threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));
  for (auto &t : threads) {
    t.join();
  }
  std::cout << alice.output() << bob.output() << charlie.output()
            << dave.output();
  return 0;
}
