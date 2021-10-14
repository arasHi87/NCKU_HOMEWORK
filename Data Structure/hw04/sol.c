#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
const int maxN = 1e3 + 7;

char ch;
int n, m, t, sum, mp[maxN][maxN], vis[maxN][maxN];
int d[8][8] = { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 }, { -1, 0 } };

void dfs(int x, int y, int cnt)
{
    while (cnt < n * m && sum < 50000) {
        if (cnt == n * m)
            return;
        if (!vis[x][y])
            vis[x][y] = 1, cnt += 1;
        mp[x][y]++, sum++;
        int idx = rand() % 8, dx = x + d[idx][0], dy = y + d[idx][0];

        while (dx < 1 || dy < 1 || dx > n || dy > m)
            idx = rand() % 8, dx = x + d[idx][0], dy = y + d[idx][1];

        x = dx, y = dy;
    }
}

int main()
{
    srand(time(NULL));
    while (scanf("%c", &ch) && ch != 'q') {
        sum = 0;
        memset(mp, 0, sizeof mp);
        memset(vis, 0, sizeof vis);

        if (ch == 'a') {
            scanf("%d%d", &n, &m);
            dfs(1, 1, 0);
        } else {
            scanf("%d", &t);
            if (t == 1) {
                n = m = 35;
                dfs(10, 10, 0);
            } else {
                n = 39, m = 19;
                dfs(1, 1, 0);
            }
        }

        getchar();
        printf("%d\n", sum);
        for (int i = 1; i <= n; i++) {
            printf("%4d", mp[i][1]);
            for (int j = 2; j <= m; j++)
                printf(" %4d", mp[i][j]);
            if (i != n || t != 2)
                puts("");
        }
    }
}