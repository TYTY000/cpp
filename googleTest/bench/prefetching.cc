#include <benchmark/benchmark.h>

static void rowMajor(benchmark::State& s) {
    int N = 1 << 12;
    int* array = new int[N * N];
    while (s.KeepRunning()) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                array[i * N + j] += j;
            }
        }
    }
}

BENCHMARK(rowMajor)->Unit(benchmark::kMillisecond);

static void columnMajor(benchmark::State& s) {
    int N = 1 << 12;
    int* array = new int[N * N];
    while (s.KeepRunning()) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                array[j * N + i] += j;
            }
        }
    }
}

BENCHMARK(columnMajor)->Unit(benchmark::kMillisecond);

static void randomStride(benchmark::State& s) {
    int N = 1 << 12;
    int* array = new int[N * N];
    while (s.KeepRunning()) {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                array[j * N + rand() % N] += j;
            }
        }
    }
}

BENCHMARK(randomStride)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
