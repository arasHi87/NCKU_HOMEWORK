#include <stdio.h>

int n, flag = 0;

void hanoi(int n, int a, int b, int c)
{
    if (n) {
        hanoi(n - 1, a, c, b);
        if (!flag)
            printf("%d %d %d", n, a, c), flag = 1;
        else
            printf("\n%d %d %d", n, a, c);
        hanoi(n - 1, b, a, c);
    }
}

int main()
{
    scanf("%d", &n);
    hanoi(n, 1, 2, 3);
}