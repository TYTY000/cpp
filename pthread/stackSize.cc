/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackSize.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:53:19 by TYTY000           #+#    #+#             */
/*   Updated: 2024/11/15 13:53:19 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include <iostream>

pthread_attr_t attr;
void *work(void *threadid) {
    double A[1000][1000];
    int i, j;
    long tid;
    size_t mystacksize;

    tid = (long)threadid;
    pthread_attr_getstacksize(&attr, &mystacksize);
    printf("Thread %ld: stack size = %li bytes \n", tid, mystacksize);
    for (i = 0; i < 1000; i++) {
        for (j = 0; j < 1000; j++) {
            A[i][j] = ((i * j) / 3.452) + (1000 - i);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    constexpr int num_threads = 8;
    pthread_t threads[num_threads];
    size_t stackSize;
    int rc{};
    long t{};
    pthread_t self{pthread_self()};
    std::cout << "Running with main pid_t = " << self << '\n';
    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &stackSize);
    std::cout << "Default stack size = " << stackSize << '\n';

    stackSize = sizeof(double) * 1000 * 1000 + 1000000L;
    std::cout << "Setting stack size = " << stackSize << '\n';
    pthread_attr_setstacksize(&attr, stackSize);

    std::cout << "Creating threads with stack size = " << stackSize << '\n';
    for (; t < num_threads; t++) {
        if (pthread_create(&threads[t], &attr, work, (void *)t)) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    printf("Created %ld threads.\n", t);
    pthread_exit(NULL);
    return 0;
}
