#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mpi.h>
#define maxN 2e5 + 7
using namespace std;

double start_time = 0.0;
int n, block, comm_size, my_rank;
int *arr, *ans, *arr_tmp, *exc_tmp, *recvcounts, *displs;

int main()
{
    // init
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    srand((my_rank + 8) << 8);
    recvcounts = (int*)malloc(sizeof(int) * comm_size);
    displs = (int*)malloc(sizeof(int) * comm_size);

    // get num and boardcast to other process
    if (my_rank == 0)
        scanf("%d", &n);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    ans = (int*)malloc(sizeof(int) * n);

    // record time
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    // calculate how many elements each process have to deal
    block = n / comm_size;
    if (my_rank < n % comm_size)
        block++;
    arr = (int*)malloc(sizeof(int) * block);
    arr_tmp = (int*)malloc(sizeof(int) * block + 1);
    exc_tmp = (int*)malloc(sizeof(int) * ((block + 1) << 1));

    // generate random number and sort it
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
    sort(arr, arr + n);

    // gather local sort result from each process and print by process 0
    for (int i = 0, tmp = 0; i < comm_size; i++) {
        recvcounts[i] = n / comm_size;
        if (i < n % comm_size)
            recvcounts[i]++;
        displs[i] = tmp, tmp += recvcounts[i];
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gatherv(arr, block, MPI_INT, ans, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    if (my_rank == 0) {
        for (int i = 0; i < comm_size; i++) {
            printf("Process %d local sort:", i);
            for (int j = 0; j < recvcounts[i]; j++)
                printf("%d ", ans[displs[i] + j]);
            puts("");
        }
    }

    // odd-even sort
    for (int i = 0, partner, L, R, cnt; i < comm_size; i++) {
        if (i & 1)
            partner = my_rank & 1 ? my_rank + 1 : my_rank - 1;
        else
            partner = my_rank & 1 ? my_rank - 1 : my_rank + 1;
        if (partner == -1 || partner == comm_size)
            continue;

        // exchange the respective arrays
        if (my_rank & 1) {
            MPI_Send(arr, block, MPI_INT, partner, 0, MPI_COMM_WORLD);
            MPI_Recv(arr_tmp, recvcounts[partner], MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            MPI_Recv(arr_tmp, recvcounts[partner], MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(arr, block, MPI_INT, partner, 0, MPI_COMM_WORLD);
        }

        // sort, L is self index and R is partner index
        L = R = cnt = 0;
        while (cnt < block + recvcounts[partner]) {
            if (L >= block)
                exc_tmp[cnt++] = arr_tmp[R++];
            else if (R >= recvcounts[partner])
                exc_tmp[cnt++] = arr[L++];
            else if (arr[L] < arr_tmp[R])
                exc_tmp[cnt++] = arr[L++];
            else
                exc_tmp[cnt++] = arr_tmp[R++];
        }

        for (int j = 0; j < block; j++)
            arr[j] = (my_rank > partner ? exc_tmp[j + block] : exc_tmp[j]);
    }

    // gather sort result and print by process 0
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gatherv(arr, block, MPI_INT, ans, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    if (my_rank == 0) {
        printf("Answer: ");
        for (int i = 0; i < n; i++)
            printf("%d ", ans[i]);
        puts("");
        printf("Finished in time %f secs.\n", MPI_Wtime() - start_time);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}