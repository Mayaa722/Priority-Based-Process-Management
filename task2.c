#include <omp.h>
#include <stdio.h>

int main() {
    int N = 100;
    int sum = 0;
    int partial_sum[4] = {0};

    int nthreads = omp_get_max_threads();
    printf("Number of available threads: %d\n", nthreads);

    omp_set_num_threads(4);

#pragma omp parallel
    {
        int tid = omp_get_thread_num();

#pragma omp single
        {
            printf("Number of threads inside parallel: %d\n", omp_get_num_threads());
        }

        printf("I'm in thread: %d\n", tid);

#pragma omp for
        for (int i = 1; i <= N; i++) {
            partial_sum[tid] += i;
        }
    }

    
    for (int i = 0; i < 4; i++) {
        sum += partial_sum[i];
    }

    printf("Final sum from 1 to %d is: %d\n", N, sum);

    return 0;
}
