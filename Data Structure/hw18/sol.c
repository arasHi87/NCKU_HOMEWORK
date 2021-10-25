#include <stdio.h>
#include <stdlib.h>
#define maxN 1000007
#define LL long long

typedef struct {
    LL u, v, w;
} Node;

Node arr[maxN << 1];
LL n, m;
LL root[maxN], rank[maxN];

void init()
{
    for (LL i = 1; i <= n; i++)
        root[i] = i, rank[i] = 0;
}

int cmp(const void* a, const void* b)
{
    return ((Node*)a)->w - ((Node*)b)->w;
}

LL find(LL x)
{
    return root[x] == x ? x : (root[x] = find(root[x]));
}

void unite(LL x, LL y)
{
    x = find(x), y = find(y);
    if (rank[x] < rank[y])
        root[x] = y;
    else
        root[y] = x, rank[x] += (rank[x] == rank[y]);
}

LL kruskal()
{
    LL cnt = 0, ans = 0;
    qsort(arr, m, sizeof(Node), cmp);
    for (LL i = 0; i < m && cnt != m - 1; i++) {
        if (find(arr[i].u) != find(arr[i].v))
            unite(arr[i].u, arr[i].v), ans += arr[i].w, cnt++;
    }
    return ans;
}

int main()
{
    scanf("%lld%lld", &n, &m), init();
    for (LL i = 0; i < m; i++)
        scanf("%lld%lld%lld", &arr[i].u, &arr[i].v, &arr[i].w);
    printf("%lld\n", kruskal());
}