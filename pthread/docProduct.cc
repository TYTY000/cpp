#include <pthread.h>

#include <cstdlib>
#include <iostream>

struct DOTDATA {
    double *a;
    double *b;
    double sum;
    int veclen;
};

constexpr int num_threads{8};
constexpr int vec_len{100};

DOTDATA docstr;
pthread_t threads[num_threads];
pthread_mutex_t mtxSum;

void *dotProd(void *arg) {
    int i, start, end, len;
    long offset;
    double sum{}, *x, *y;
    offset = (long)arg;
    len = docstr.veclen;
    x = docstr.a, y = docstr.b;
    start = offset * len;
    end = start + len;

    for (i = start; i < end; i++) {
        sum += (x[i] * y[i]);
    }

    pthread_mutex_lock(&mtxSum);
    docstr.sum += sum;
    pthread_mutex_unlock(&mtxSum);

    pthread_exit((void*)0);
}

int main(int argc, char *argv[]) {
    long i{};
    double *a, *b;
    void *status;
    pthread_attr_t attr;
    a = (double *)malloc(num_threads * vec_len * sizeof(double));
    b = (double *)malloc(num_threads * vec_len * sizeof(double));

    for (; i < vec_len * num_threads; i++) {
        b[i] = a[i] = 1.0;
    }

    docstr.veclen = vec_len;
    docstr.a = a;
    docstr.b = b;
    docstr.sum = 0;

    pthread_mutex_init(&mtxSum, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], &attr, dotProd, (void *)i);
    }

    pthread_attr_destroy(&attr);

    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], &status);
    }

    std::cout << "Sum = " << docstr.sum << "\n";
    free(a), free(b), pthread_mutex_destroy(&mtxSum);
    pthread_exit(NULL);
    return 0;
}
