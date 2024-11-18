#include <benchmark/benchmark.h>

#include <cstdlib>
#include <execution>

using namespace std;

static void SequencedBench(benchmark::State& s) {
    int N = 1 << s.range(0);
    vector<int> v;
    v.reserve(N);

    // random_device rd{};
    // mt19937 gen{rd()};
    // uniform_int_distribution dis(0, 1);
    srand(time(NULL));

    for (size_t i = 0; i < N; i++) {
        v.emplace_back(rand() % 2);
    }

    // int sum{};
    while (s.KeepRunning()) {
        sort(execution::seq, v.begin(), v.end());
    }
}

BENCHMARK(SequencedBench)->DenseRange(10, 16)->Unit(benchmark::kMillisecond);

static void ParallelBench(benchmark::State& s) {
    int N = 1 << s.range(0);
    vector<int> v;
    v.reserve(N);

    // random_device rd{};
    // mt19937 gen{rd()};
    // uniform_int_distribution dis(0, 1);

    for (size_t i = 0; i < N; i++) {
        v.emplace_back(rand() % 2);
    }

    // int sum{};
    while (s.KeepRunning()) {
        sort(execution::par, v.begin(), v.end());
    }
}

BENCHMARK(ParallelBench)->DenseRange(10, 16)->Unit(benchmark::kMillisecond);

static void ParallelUnseqBench(benchmark::State& s) {
    int N = 1 << s.range(0);
    vector<int> v;
    v.reserve(N);

    // random_device rd{};
    // mt19937 gen{rd()};
    // uniform_int_distribution dis(0, 1);

    for (size_t i = 0; i < N; i++) {
        v.emplace_back(rand() % 2);
    }

    // int sum{};
    while (s.KeepRunning()) {
        sort(execution::par_unseq, v.begin(), v.end());
    }
}

BENCHMARK(ParallelUnseqBench)
    ->DenseRange(10, 16)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
