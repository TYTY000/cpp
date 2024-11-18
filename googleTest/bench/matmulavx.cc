#include <benchmark/benchmark.h>
#include <immintrin.h>

#include <cstdlib>

inline float prod_8(float *m_v, float *v) {
    union {
        float r[8];
        __m256 rv;
    };

    rv = _mm256_dp_ps(_mm256_load_ps(m_v), _mm256_load_ps(v), 0xF1);

    return r[0] + r[4];
}

// float vv_prod(float *m_v, float *v, size_t dim) {
//     float res{};

//     for (size_t i = 0; i < dim; i += 8) {
//         res += prod_8(m_v + i, v + i);
//     }

//     return res;
// }

void matmul(float *A, float *B, float *C, size_t dim) {
    for (size_t i = 0; i < dim; i++) {
        for (size_t j = 0; j < dim; j++) {
            float sum{};
            for (size_t k = 0; k < dim; k += 8) {
                sum += prod_8(&A[i * dim + k], &B[k * dim + j]);
            }
            C[i * dim + j] += sum;
        }
    }
}

float *allocate(size_t bytes) {
    void *memory = std::aligned_alloc(64, bytes);
    if (!memory) {
        abort();
    }
    return static_cast<float *>(memory);
}

static void matmulBench(benchmark::State &s) {
    int dim = 1 << s.range(0);
    float *M = allocate(sizeof(float) * dim * dim);
    float *U = allocate(sizeof(float) * dim * dim);
    float *V = allocate(sizeof(float) * dim * dim);

    for (size_t i = 0; i < dim; i++) {
        U[i] = std::rand() % 100;
        V[i] = 0;
        for (size_t j = 0; j < dim; j++) {
            M[i * dim + j] = std::rand() % 100;
        }
    }

    while (s.KeepRunning()) {
        matmul(M, U, V, dim);
    }

    delete[] M;
    delete[] U;
    delete[] V;

    s.SetItemsProcessed(dim * dim * dim * s.iterations());
    s.SetBytesProcessed(sizeof(float) * dim * dim * dim * s.iterations());
}

BENCHMARK(matmulBench)->DenseRange(6, 8);

BENCHMARK_MAIN();
