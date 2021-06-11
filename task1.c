#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char* argv[])
{
    int thread_count=strtol(argv[1],NULL,10);
    # pragma omp parallel num_threads(thread_count)
    {
        int my_rank=omp_get_thread_num();
        int thread_count=omp_get_num_threads();
        # pragma omp single
            printf("Thread %d print a sentence.\n",my_rank);
        # pragma omp master
            printf("Thread %d print another sentence;\nWe have %d thread.\n",my_rank,thread_count);
    }
    return 0;
}