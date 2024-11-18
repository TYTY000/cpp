#include <array>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

static void Serial() {
    const int num_iter = 1 << 27;
    const int num_threads = 1;
    std::atomic<int> counter = 0;
    auto work = [&]() -> void {
        for (size_t i = 0; i < num_iter; i++) {
            counter++;
        }
    };
    std::vector<std::jthread> threads;
    for (size_t i = 0; i < num_threads; i++) {
        threads.emplace_back(work);
    }
}

static void DirectSharing() {
    const int num_iter = 1 << 27;
    const int num_threads = 4;
    const int element_per_thread = num_iter / num_threads;
    std::atomic<int> counter = 0;
    auto work = [&]() -> void {
        for (size_t i = 0; i < element_per_thread; i++) {
            counter++;
        }
    };
    std::vector<std::jthread> threads;
    for (size_t i = 0; i < num_threads; i++) {
        threads.emplace_back(work);
    }
}

static void FalseSharing() {
    const int num_iter = 1 << 27;
    const int num_threads = 4;
    const int element_per_thread = num_iter / num_threads;
    std::array<std::atomic<int>, 4> counters{0, 0, 0, 0};
    std::atomic<int> final_sum{};
    auto work = [&](int threadIdx) -> void {
        for (size_t i = 0; i < element_per_thread; i++) {
            counters[threadIdx]++;
        }
        final_sum += counters[threadIdx];
    };
    std::vector<std::jthread> threads;
    for (size_t i = 0; i < num_threads; i++) {
        threads.emplace_back(work, i);
    }
}

struct AlignedAtomic{
    alignas(64) std::atomic<int> counter{};
};

static void TrueSharing() {
    const int num_iter = 1 << 27;
    const int num_threads = 4;
    const int element_per_thread = num_iter / num_threads;
    std::array<AlignedAtomic, 4> counters{0, 0, 0, 0};
    std::atomic<int> final_sum{};
    auto work = [&](int threadIdx) -> void {
        for (size_t i = 0; i < element_per_thread; i++) {
            counters[threadIdx].counter++;
        }
        final_sum += counters[threadIdx].counter;
    };
    std::vector<std::jthread> threads;
    for (size_t i = 0; i < num_threads; i++) {
        threads.emplace_back(work, i);
    }
}

int main(int argc, char *argv[]) {
    auto start1 = std::chrono::high_resolution_clock::now();
    Serial();
    auto end1 = std::chrono::high_resolution_clock::now();
    std::cout << "Serial run : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end1 -
                                                                       start1)
              << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    DirectSharing();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "DirectSharing run : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end2 -
                                                                       start2)
              << std::endl;

    auto start3 = std::chrono::high_resolution_clock::now();
    FalseSharing();
    auto end3 = std::chrono::high_resolution_clock::now();
    std::cout << "FalseSharing run : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end3 -
                                                                       start3)
              << std::endl;

    auto start4 = std::chrono::high_resolution_clock::now();
    TrueSharing();
    auto end4 = std::chrono::high_resolution_clock::now();
    std::cout << "TrueSharing run : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end4 -
                                                                       start4)
              << std::endl;

    return 0;
}
