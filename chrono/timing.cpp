#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ratio>
// #include <omp.h>

std::chrono::high_resolution_clock::time_point getTime() {
    return std::chrono::high_resolution_clock::now();
}

int main(int argc, char *argv[]) {
    constexpr int N = 1 << 24;
    int *a = new int[N];
    int *b = new int[N];
    int *c = new int[N];

// #pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
    }

    auto start = getTime();

    // auto start = omp_get_wtime();
// #pragma omp parallel for
    for (size_t i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    auto end = getTime();
    // auto end = omp_get_wtime();

    auto span =
        std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(end - start);
    // auto span = end - start;
    std::cout << "time : " << span.count() << " ns" << std::endl;
    // std::cout << "time : " << span << std::endl;
    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}
