#include <stdio.h>
#include <string.h>

struct step {
    int x, y;
} ans[100];

int n, m, idx = 0, mp[100][100], vis[100][100];
int d[8][8] = { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 } };

int dfs(int x, int y)
{
    vis[x][y] = 1;
    if (x == n && y == m) {
        ans[++idx] = (struct step) { x, y };
        return 1;
    }
    for (int i = 0, dx, dy; i < 8; i++) {
        dx = x + d[i][0], dy = y + d[i][1];
        if (!mp[dx][dy] && !vis[dx][dy] && dfs(dx, dy)) {
            ans[idx++] = (struct step) { dx, dy };
            return 1;
        }
    }
    return 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(mp, -1, sizeof mp);
    memset(vis, 0, sizeof vis);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &mp[i][j]);

    dfs(1, 1);

    if (idx) {
        printf("0 0");
        for (int i = idx - 1; i >= 1; i--)
            printf("\n%d %d", ans[i].x - 1, ans[i].y - 1);
    } else {
        printf("no answer");
    }
}