#include <benchmark/benchmark.h>
#include <immintrin.h>

#include <algorithm>
#include <cstring>
#include <execution>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

static void dpBench(benchmark::State &s) {
    // std::random_device rd{};
    std::mt19937 gen{111};
    std::uniform_real_distribution dis(0.f, 1.f);
    const int num_elem = 1 << 15;
    std::vector<float> v1;
    std::vector<float> v2;
    std::generate_n(std::back_inserter(v1), num_elem, [&] { return dis(gen); });
    std::generate_n(std::back_inserter(v2), num_elem, [&] { return dis(gen); });

    float *ans = new float{};
    for (auto _ : s) {
        *ans = std::transform_reduce(std::execution::unseq, v1.begin(),
                                     v1.end(), v2.begin(), 0.f);
        // std::cout << *ans << std::endl;
    }
}

BENCHMARK(dpBench)->Unit(benchmark::kMicrosecond);

// Hand-tuned dot product
float dot_product(const __m256 *v1, const __m256 *v2,
                  size_t num_packed_elements) {
    auto tmp = 0.0f;
    for (size_t i = 0; i < num_packed_elements; i++) {
        std::array<float, 8> unpacked;
        __m256 result = _mm256_dp_ps(v1[i], v2[i], 0xf1);
        _mm256_storeu_ps(unpacked.data(), result);

        // Perform the final add
        tmp += unpacked[0] + unpacked[4];
    }
    return tmp;
}

static void dot_product_bench(benchmark::State &s) {
    // Get the size of the vector
    const size_t num_elements = 1 << 15;
    const size_t elements_per_reg = 8;
    const size_t num_packed_elements = num_elements / elements_per_reg;

    // Create random number generator
    // std::random_device rd;
    std::mt19937 mt(111);
    std::uniform_real_distribution dist(0.0f, 1.0f);

    // Allocate __m256 aligned to 32B
    auto v1 = static_cast<__m256 *>(
        std::aligned_alloc(32, num_packed_elements * sizeof(__m256)));
    auto v2 = static_cast<__m256 *>(
        std::aligned_alloc(32, num_packed_elements * sizeof(__m256)));

    // Create random numbers for v1 and v2
    for (size_t i = 0; i < num_packed_elements; i++) {
        v1[i] = _mm256_set_ps(dist(mt), dist(mt), dist(mt), dist(mt), dist(mt),
                              dist(mt), dist(mt), dist(mt));
        v2[i] = _mm256_set_ps(dist(mt), dist(mt), dist(mt), dist(mt), dist(mt),
                              dist(mt), dist(mt), dist(mt));
    }

    // Perform dot product
    float *result = new float;
    for (auto _ : s) {
        *result = dot_product(v1, v2, num_packed_elements);
        // std::cout << *result << std::endl;
    }

    // Free memory when we're done
    free(v1);
    free(v2);
}
BENCHMARK(dot_product_bench)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
