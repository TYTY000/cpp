// #include <immintrin.h>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <semaphore>
#include <thread>
void reorder(std::binary_semaphore& start, std::counting_semaphore<2>& end,
             int& write, int& read, int& reg) {
    while (true) {
        start.acquire();

        write = 1;

        // _mm_mfence();
        std::atomic_thread_fence(std::memory_order::seq_cst);

        reg = read;

        end.release();
    }
}

int main() {
    std::binary_semaphore start1{0};
    std::binary_semaphore start2{0};
    std::counting_semaphore<2> done{0};

    int x = 0, y = 0, r1 = 0, r2 = 0;

    std::jthread t1{[&]() { reorder(start1, done, x, y, r1); }};
    std::jthread t2{[&]() { reorder(start2, done, y, x, r2); }};

    int three{}, two{}, one{};
    for (size_t i = 0;; i++) {
        x = 0;
        y = 0;

        start1.release();
        start2.release();
        done.acquire();
        done.acquire();

        auto reordering = (r1 == 0) and (r2 == 0);
        if (reordering) {
            std::cout << "ERROR! r1 = " << r1 << ", r2 = " << r2
                      << ", Iteration: " << i << "\n";
            std::cout << "01 : " << one << " 10 : " << two << " 11 : " << three
                      << '\n';
            abort();
        } else if (r1 == 1) {
            if (r2 == 1) {
                three++;
            } else {
                two++;
            }
        } else {
            one++;
        }
    }

    return 0;
}
