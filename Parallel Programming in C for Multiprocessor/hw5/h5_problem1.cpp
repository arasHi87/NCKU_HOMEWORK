#include <iostream>
#include <omp.h>
#include <string.h>
#define NUM_THREADS 8
using namespace std;

void sort(int a[], int n)
{
    int i, j, cnt;
    int* tmp = (int*)malloc(n * sizeof(int));

#pragma omp parallel for private(i, j, cnt) shared(a, n, tmp)
    for (i = 0; i < n; i++) {
        cnt = 0;
        for (j = 0; j < n; j++)
            if ((a[j] < a[i]) || (a[j] == a[i] && j < i))
                cnt++;
        tmp[cnt] = a[i];
        printf("%d is locate in %d\n", a[i], cnt);
    }

    memcpy(a, tmp, n * sizeof(int));
}

int main()
{
    int i;
    int a[] = { 5, 2, 9, 1, 0, 3, 8, 4, 7, 6 };
    int n = sizeof(a) / sizeof(int);

    omp_set_num_threads(NUM_THREADS);
    sort(a, n);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    puts("");
}