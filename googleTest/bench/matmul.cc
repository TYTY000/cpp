#include <benchmark/benchmark.h>

#include <cstdlib>

void matmul(float *a, float *b, float *c, size_t dim) {
    for (size_t i = 0; i < dim; i++) {
        for (size_t j = 0; j < dim; j++) {
            c[i * dim + j] = 0;
            for (size_t k = 0; k < dim; k++) {
                c[i * dim + j] += a[i * dim + k] * b[k * dim + j];
            }
        }
    }
}

static void matmulBench(benchmark::State &s) {
    int dim = 1 << s.range(0);
    float *M = new float[dim * dim];
    float *A = new float[dim * dim];
    float *B = new float[dim * dim];

    for (size_t i = 0; i < dim; i++) {
        for (size_t j = 0; j < dim; j++) {
            A[i * dim + j] = std::rand() % 100;
            B[i * dim + j] = std::rand() % 100;
        }
    }

    while (s.KeepRunning()) {
        matmul(A, B, M, dim);
    }

    delete[] M;
    delete[] A;
    delete[] B;

    s.SetItemsProcessed(dim * dim * dim * s.iterations());
    s.SetBytesProcessed(sizeof(float) * dim * dim * dim * s.iterations());
}

BENCHMARK(matmulBench)->DenseRange(6, 8);

BENCHMARK_MAIN();
