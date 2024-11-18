#include <tbb/concurrent_queue.h>

#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>

#include "tick.h"

void baseline() {
    // Number of elements to add to the queue
    const int num_elements = 1 << 25;

    // Divide the work by threads
    const int num_threads = 8;
    const int elements_per_thread = num_elements / num_threads;

    // Create a queue
    std::queue<int> queue;

    // Create a mutex to guard the queue
    std::mutex m;

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(1, 100);

    // Create a work function to add elements
    auto work = [&]() {
        for (int i = 0; i < elements_per_thread; i++) {
            auto val = dis(gen);
            std::lock_guard<std::mutex> lg(m);
            queue.push(val);
        }
    };

    // Spawn threads
    std::vector<std::jthread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(work);
    }
}

void concurrent_container() {
    // Number of elements to add to the queue
    const int num_elements = 1 << 25;

    // Divide the work by threads
    const int num_threads = 8;
    const int elements_per_thread = num_elements / num_threads;

    // Create a queue
    tbb::concurrent_queue<int> queue;

    // Create a mutex to guard the queue
    std::mutex m;

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(1, 100);

    // Create a work function to add elements
    auto work = [&]() {
        for (int i = 0; i < elements_per_thread; i++) {
            queue.push(dis(gen));
        }
    };

    // Spawn threads
    std::vector<std::jthread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(work);
    }
}

int main(int argc, char *argv[]) {
    std::cout << "baseline ";
    tick(baseline);
    std::cout << "concurrent_container";
    tick(concurrent_container);

    return 0;
}
