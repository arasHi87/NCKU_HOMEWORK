#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 107

int t, n, m;
int arr[maxN][maxN], vis[maxN];

void dfs(int x)
{
    printf("%d ", x), vis[x] = 1;
    for (int i = 0; i < n; i++)
        if (arr[x][i] && !vis[i])
            dfs(i);
}

int main()
{
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &arr[i][j]);
        dfs(m), puts("");
    }
}