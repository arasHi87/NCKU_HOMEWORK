/* circuitSatifiability.c solves the Circuit Satisfiability
 *  Problem using a brute-force sequential solution.
 *
 *   The particular circuit being tested is "wired" into the
 *   logic of function 'checkCircuit'. All combinations of
 *   inputs that satisfy the circuit are printed.
 *
 *   16-bit version by Michael J. Quinn, Sept 2002.
 *   Extended to 32 bits by Joel C. Adams, Sept 2013.
 */

#include "mpi.h"
#include <limits.h> // UINT_MAX
#include <stdio.h> // printf()

int checkCircuit(int, int);

int main(int argc, char* argv[])
{
    int count = 0; /* number of solutions */
    int comm_size, my_rank;
    double startTime = 0.0, totalTime = 0.0; /* time cost */

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    startTime = MPI_Wtime();

    // count
    for (int i = my_rank; i <= USHRT_MAX; i += comm_size)
        count += checkCircuit(my_rank, i);

    // merge
    int mid = comm_size, tmp;
    while (1) {
        mid >>= 1;
        if (my_rank < mid)
            MPI_Recv(&tmp, 1, MPI_INT, my_rank + mid, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE), count += tmp;
        else if (my_rank < (mid << 1))
            MPI_Send(&count, 1, MPI_INT, my_rank - mid, 0, MPI_COMM_WORLD);
        else
            break;
    }

    totalTime = MPI_Wtime() - startTime;
    MPI_Finalize();
    if (my_rank == 0) {
        printf("\nA total of %d solutions were found.\n\n", count);
        printf("Process %d finished in time %f secs.\n", my_rank, totalTime);
        fflush(stdout);
    }
    return 0;
}

/* EXTRACT_BIT is a macro that extracts the ith bit of number n.
 *
 * parameters: n, a number;
 *             i, the position of the bit we want to know.
 *
 * return: 1 if 'i'th bit of 'n' is 1; 0 otherwise
 */

#define EXTRACT_BIT(n, i) ((n & (1 << i)) ? 1 : 0)

/* checkCircuit() checks the circuit for a given input.
 * parameters: id, the id of the process checking;
 *             bits, the (long) rep. of the input being checked.
 *
 * output: the binary rep. of bits if the circuit outputs 1
 * return: 1 if the circuit outputs 1; 0 otherwise.
 */

#define SIZE 16

int checkCircuit(int id, int bits)
{
    int v[SIZE]; /* Each element is a bit of bits */
    int i;

    for (i = 0; i < SIZE; i++)
        v[i] = EXTRACT_BIT(bits, i);

    if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
        && (!v[3] || !v[4]) && (v[4] || !v[5])
        && (v[5] || !v[6]) && (v[5] || v[6])
        && (v[6] || !v[15]) && (v[7] || !v[8])
        && (!v[7] || !v[13]) && (v[8] || v[9])
        && (v[8] || !v[9]) && (!v[9] || !v[10])
        && (v[9] || v[11]) && (v[10] || v[11])
        && (v[12] || v[13]) && (v[13] || !v[14])
        && (v[14] || v[15])) {
        printf("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d \n", id,
            v[15], v[14], v[13], v[12],
            v[11], v[10], v[9], v[8], v[7], v[6], v[5], v[4], v[3], v[2], v[1], v[0]);
        fflush(stdout);
        return 1;
    } else {
        return 0;
    }
}
