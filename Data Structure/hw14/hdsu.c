#include <stdio.h>
#include <stdlib.h>
#define maxN 10007

char str[10];
int n, root[maxN], rank[maxN];

void init()
{
    for (int i = 0; i < maxN; i++)
        root[i] = i, rank[i] = 0;
}

int find(int x)
{
    return root[x] == x ? x : (root[x] = find(root[x]));
}

void unite(int x, int y)
{
    x = find(x), y = find(y);
    if (x != y) {
        if (rank[x] <= rank[y])
            root[y] = x, rank[x] -= (rank[x] == rank[y]);
        else
            root[x] = y;
    }
}

int main()
{
    int x, y;
    init();
    while (~scanf("%d", &n)) {
        if (n)
            scanf("%d", &x), find(x);
        else
            scanf("%d%d", &x, &y), unite(x, y);
    }
}