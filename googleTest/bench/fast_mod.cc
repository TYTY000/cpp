#include <benchmark/benchmark.h>

#include <algorithm>
#include <iterator>
#include <random>

using namespace std;

static void custom_args(benchmark::internal::Benchmark* b) {
    for (size_t i = 1 << 4; i <= 1 << 10; i <<= 2) {
        for (size_t j : {32, 128, 224}) {
            b = b->ArgPair(i, j);
        }
    }
}

static void baseMod(benchmark::State& s) {
    int N = s.range(0);

    int ceil = s.range(1);

    vector<int> input;
    vector<int> output;
    input.resize(N);
    output.resize(N);

    mt19937 gen;
    gen.seed(random_device{}());
    uniform_int_distribution dist(0, 255);
    generate_n(back_inserter(input), N, [&]{return dist(gen);});
    // ranges::generate_n(input.begin(), N, [&](){return dist(gen);});

    while (s.KeepRunning()) {
        for (size_t i = 0; i < N; i++) {
            output[i] = input[i] % ceil;
        }
    }
}

BENCHMARK(baseMod)->Apply(custom_args);

static void fastMod(benchmark::State& s) {
    int N = s.range(0);

    int ceil = s.range(1);

    vector<int> input;
    vector<int> output;
    input.resize(N);
    output.resize(N);

    mt19937 gen;
    gen.seed(random_device{}());
    uniform_int_distribution dist(0, 255);
    for (auto& elem : input) {
        elem = dist(gen);
    }

    while (s.KeepRunning()) {
        for (size_t i = 0; i < N; i++) {
            output[i] = __builtin_expect((input[i] >= ceil), 0)
                            ? input[i] % ceil
                            : input[i];
        }
    }
}

BENCHMARK(fastMod)->Apply(custom_args);

BENCHMARK_MAIN();
