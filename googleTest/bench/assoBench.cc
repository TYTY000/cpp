#include <benchmark/benchmark.h>

#include <cstdlib>

static void assoBench(benchmark::State& s) {
    int step = 1 << s.range(0);

    int N = 1 << 24;
    char* c = new char[N];

    for (size_t i = 0; i < N; i++) {
        c[i] = rand() % 100;
    }

    while (s.KeepRunning()) {
        int i{};
        for (size_t iter = 0; iter < 10000; iter++) {
            c[i]++;
            i += step;
            i %= N;
        }
    }

    delete[] c;
}

BENCHMARK(assoBench)->DenseRange(0,16)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
