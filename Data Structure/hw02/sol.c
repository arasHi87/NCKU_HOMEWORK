#include <stdio.h>

int n;

void hanoi(int n, int a, int b, int c)
{
    if (n) {
        hanoi(n - 1, a, c, b);
        printf("%d %d %d\n", n, a, c);
        hanoi(n - 1, b, a, c);
    }
}

int main()
{
    scanf("%d", &n);
    hanoi(n, 1, 2, 3);
}