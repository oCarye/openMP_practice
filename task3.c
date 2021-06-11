#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char* argv[])
{
    int thread_count=strtol(argv[1],NULL,10);
    int m,n;
    printf("请输入矩阵的行数m与列数n，以空格分隔：\n");
    scanf("%d %d",&m,&n);
    float** a=malloc(m*sizeof(float*));
    printf("请输入矩阵元素：\n");
    for (int i=0;i<m;i++)
    {
        a[i]=malloc(n*sizeof(float));
        for (int j=0;j<n;j++)
            scanf("%f",a[i]+j);
    }
    // printf("Success!\n");
    /*
    for (int i=0;i<m;i++)
    {
        for (int j=0;j<n;j++)
            printf("%.2f ",a[i][j]);
        printf("\n");
    }
    */
    float max=-1000,min=1000;
    #pragma omp parallel num_threads(thread_count)
    {
        #pragma omp for
            for (int i=0;i<m;i++)
            {
                float local_max=max, local_min=min;
                for (int j=0;j<n;j++)
                {
                    if (a[i][j]>local_max) local_max=a[i][j];
                    if (a[i][j]<local_min) local_min=a[i][j];
                }
                #pragma omp critical
                {
                    if (local_max>max) max=local_max;
                    if (local_min<min) min=local_min;
                }
            }
    }
    printf("The max number is %.2f\nThe min number is %.2f",max,min);
    return 0;
}