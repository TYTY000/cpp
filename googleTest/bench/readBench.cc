#include <benchmark/benchmark.h>

#include <cstdlib>

void matmul(float *a, float *b, float *c, size_t dim) {
    for (size_t i = 0; i < dim; i++) {
        for (size_t j = 0; j < dim; j++) {
            c[i] += b[j] * a[i * dim + j];
        }
    }
}

static void matmulBench(benchmark::State &s) {
    int dim = 1 << s.range(0);
    float *matrix = new float[dim * dim];

    for (size_t i = 0; i < dim * dim; i++) {
        matrix[i] = std::rand() % 100;
    }

    float sink{};

    while (s.KeepRunning()) {
        for (size_t i = 0; i < dim * dim; i++) {
            sink = matrix[i];
        }
    }

    benchmark::DoNotOptimize(sink);

    delete[] matrix;

    s.SetItemsProcessed(dim * dim * s.iterations());
    s.SetBytesProcessed(sizeof(float) * dim * dim * s.iterations());
}

BENCHMARK(matmulBench)->DenseRange(8, 10);

BENCHMARK_MAIN();
