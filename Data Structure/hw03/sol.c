#include <stdio.h>
const int maxN = 2e5 + 10;

typedef struct {
    int row, col, val;
} matrix;

int a, b, c, idx = 0;
matrix arr[maxN];

void fastTranspose(matrix x[])
{
    matrix y[maxN];
    int nzr[maxN] = { 0 }, sp[maxN] = { 0 };

    y[0].row = x[0].col;
    y[0].col = x[0].row;
    y[0].val = x[0].val;
    sp[0] = 1;

    for (int i = 1; i <= x[0].val; i++)
        nzr[x[i].col]++;
    for (int i = 1; i <= x[0].col; i++)
        sp[i] = sp[i - 1] + nzr[i - 1];
    for (int i = 1, j; i <= x[0].val; i++) {
        j = sp[x[i].col]++;
        y[j].row = x[i].col;
        y[j].col = x[i].row;
        y[j].val = x[i].val;
    }

    printf("%d %d %d", y[0].col, y[0].row, y[0].val);
    for (int i = 1; i < idx; i++)
        printf("\n%d %d %d", y[i].row, y[i].col, y[i].val);
}

int main()
{
    while (~scanf("%d%d%d", &a, &b, &c)) {
        arr[idx++] = (matrix) { a, b, c };
    }
    fastTranspose(arr);
}