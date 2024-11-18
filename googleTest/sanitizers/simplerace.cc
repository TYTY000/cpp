// #include <cassert>
// #include <mutex>
// #include <thread>
// #include <vector>

// int main() {
//     // Number of total increments and increments per thread
//     const int num_increments = 1 << 20;
//     const int num_threads = 8;
//     const int increments_per_thread = num_increments / num_threads;

//     // Incremented by each thread
//     volatile int sink = 0;

//     std::mutex m;
//     // Create a work function to add elements
//     auto work = [&]() {
//         for (int i = 0; i < increments_per_thread; i++) {
//             std::unique_lock lk(m);
//             sink = sink + 1;
//         }
//     };

//     // Spawn threads
//     std::vector<std::jthread> threads;
//     for (int i = 0; i < num_threads; i++) {
//         threads.emplace_back(work);
//     }

//     // Join the threads and check the result
//     for (auto &thread : threads) thread.join();
//     assert(sink == num_increments);
//     return 0;
// }
#include <pthread.h>
#include <stdio.h>

#include <map>
#include <mutex>
#include <string>

typedef std::map<std::string, std::string> map_t;

void *threadfunc(void *p) {
    map_t &m = *(map_t *)p;
    m["foo"] = "bar";
    return 0;
}

int main() {
    map_t m;
    pthread_t t;
    pthread_create(&t, 0, threadfunc, &m);
    pthread_join(t, 0);
    printf("foo=%s\n", m["foo"].c_str());
}
