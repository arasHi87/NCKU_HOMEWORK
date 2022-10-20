#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LL long long

time_t t;
int comm_size, my_rank, mid;
LL N, result = 0;
double startTime = 0.0, totalTime = 0.0;

double random_double()
{
    unsigned int rnd;
    rnd = (rand() & 0x7fff) | ((rand() & 0x7fff) << 15);
    return (double)rnd / (double)(0x3fffffff);
}

int monte_carlo()
{
    double x, y;
    x = random_double(), y = random_double();
    if ((x * x + y * y) <= 1.0)
        return 1;
    return 0;
}

int main()
{
    srand((unsigned)time(&t));
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
        scanf("%lld", &N);

    // boardcast N
    mid = 1;
    while (mid < comm_size) {
        if (my_rank < mid)
            MPI_Send(&N, 1, MPI_LONG_LONG, my_rank + mid, 0, MPI_COMM_WORLD);
        else if (my_rank < (mid << 1))
            MPI_Recv(&N, 1, MPI_LONG_LONG, my_rank - mid, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        mid <<= 1;
    }

    startTime = MPI_Wtime();

    // calculate
    for (LL i = my_rank; i <= N; i += comm_size)
        result += monte_carlo();

    // merge
    LL tmp;
    mid = comm_size;
    while (1) {
        mid >>= 1;
        if (my_rank < mid)
            MPI_Recv(&tmp, 1, MPI_LONG_LONG, my_rank + mid, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE), result += tmp;
        else if (my_rank < (mid << 1))
            MPI_Send(&result, 1, MPI_LONG_LONG, my_rank - mid, 0, MPI_COMM_WORLD);
        else
            break;
    }

    // final
    if (my_rank == 0) {
        totalTime = MPI_Wtime() - startTime;
        printf("pi is %lf\n", (double)(4 * (double)result / (double)N));
        printf("Process %d finished in time %f secs.\n", my_rank, totalTime);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}