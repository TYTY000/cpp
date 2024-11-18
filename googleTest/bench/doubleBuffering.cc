#include <benchmark/benchmark.h>
#include <chrono>
#include <iostream>
#include <random>
#include <semaphore>
#include <span>
#include <thread>
#include <vector>

void generate_data(std::span<int> data) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution dis(1, 100);
    for (auto& elem : data) {
        elem = dis(gen);
    }
}

void process_data(std::span<int> data) {
    for (size_t i = 0; i < 5; i++) {
        for (auto& elem : data) {
            elem %= elem + 1;
        }
    }
}

void baseline() {
    std::vector<int> data;
    data.resize(1 << 20);

    for (size_t i = 0; i < 100; i++) {
        generate_data(data);
        process_data(data);
    }
}

void doubleBuffering() {
    std::vector<int> data1;
    data1.resize(1 << 20);
    std::vector<int> data2;
    data2.resize(1 << 20);

    std::binary_semaphore process{0};
    std::binary_semaphore generate{1};

    const int num_iter = 100;

    auto data_gen = [&]() {
        for (size_t i = 0; i < num_iter; i++) {
            generate_data(data1);
            generate.acquire();
            data1.swap(data2);
            process.release();
        }
    };

    auto data_pro = [&]() {
        for (size_t i = 0; i < num_iter; i++) {
            process.acquire();
            process_data(data2);
            generate.release();
        }
    };

    std::jthread gen{data_gen};
    std::jthread pro{data_pro};
}
static void BM_Baseline(benchmark::State& state) {
    for (auto _ : state) {
        baseline();
    }
}
BENCHMARK(BM_Baseline)->Unit(benchmark::kSecond);
static void BM_DoubleBuffering(benchmark::State& state) {
    for (auto _ : state) {
        doubleBuffering();
    }
}
BENCHMARK(BM_DoubleBuffering)->Unit(benchmark::kSecond);
BENCHMARK_MAIN();
// template <typename F>
// void tick(F f){
//     auto start = std::chrono::high_resolution_clock::now();
//     f();
//     auto end = std::chrono::high_resolution_clock::now();
//     std::cout << "takes " <<
//     std::chrono::duration_cast<std::chrono::milliseconds>(end - start) <<
//     std::endl;
// }
// int main(int argc, char* argv[]) {
//     std::cout << "baseline ";
//     tick(baseline);
//     std::cout << "doubleBuffering ";
//     tick(doubleBuffering);
//     return 0; }
