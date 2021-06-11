#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char* argv[])
{
    int thread_count=strtol(argv[1],NULL,10);
    #pragma omp parallel num_threads(thread_count) shared(thread_count)
    {
        int my_rank=omp_get_thread_num();
        #pragma omp master
            thread_count=omp_get_num_threads();
        #pragma omp single
            printf("We totally have %d threads.\n",thread_count);
        #pragma omp sections
        {
            #pragma omp section
                printf("Thread %d print sentence 1.\n",my_rank);
            #pragma omp section
                printf("Thread %d print sentence 2.\n",my_rank);
            #pragma omp section
                printf("Thread %d print sentence 3.\n",my_rank);
            // printf("Over.\n");  sections模块里不能有非section语句
        }
    }
    return 0;
}