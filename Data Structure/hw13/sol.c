#include <stdio.h>
#include <stdlib.h>
#define maxN 10007

char str[10];
int n, m, t, root[maxN], rank[maxN];

void init(int x)
{
    for (int i = 0; i < x; i++)
        root[i] = i, rank[i] = 0;
}

int find(int x)
{
    return root[x] == x ? x : (root[x] = find(root[x]));
}

void unite(int x, int y)
{
    x = find(x), y = find(y);
    if (rank[x] < rank[y])
        root[y] = x;
    else if (rank[x] > rank[y])
        root[x] = y;
    else if (root[x] != root[y] && rank[x] == rank[y])
        rank[x]--, root[y] = x;
}

int main()
{
    int x, y;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m), init(n);
        while (m--) {
            scanf("%s", str);
            if (str[0] == 'u')
                scanf("%d%d", &x, &y), unite(x, y);
            else if (str[0] == 'f') {
                scanf("%d", &x);
                printf("%d\n", find(root[x]));
            } else {
                scanf("%d%d", &x, &y);
                find(root[x]) == find(root[y]) ? puts("true") : puts("false");
            }
        }
    }
}