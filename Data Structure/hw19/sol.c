#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 1000007

typedef struct edge {
    int to, next, w;
} Edge;

Edge edge[maxN << 1];
int n, s, cnt = 0;
int head[maxN], vis[maxN], ans[maxN];

void init()
{
    cnt = 0;
    memset(head, -1, sizeof head);
    memset(ans, 0, sizeof ans);
}

void addedge(int u, int v, int w)
{
    edge[cnt].w = w;
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int x)
{
    vis[x] = 1;
    for (int i = head[x]; ~i; i = edge[i].next)
        if (!vis[edge[i].to])
            ans[edge[i].to] += (edge[i].w + ans[x]), dfs(edge[i].to);
    return;
}

int main()
{
    scanf("%d", &n), init();
    for (int i = 1, u, v, w; i <= n - 1; i++) {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }

    scanf("%d", &s), ans[s] = 0, dfs(s);
    for (int i = 1; i <= n; i++)
        printf("%d %d\n", i, ans[i]);
}