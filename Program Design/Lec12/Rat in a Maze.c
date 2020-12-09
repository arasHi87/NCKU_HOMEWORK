int vis[n][n];
int d[4][2]={{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool visit(char map[][n], int arr[][n], int x, int y) {
	vis[x][y]=1, arr[x][y]=1;

	if (x==n-1 && y==n-1)
		return 1;

	for (int i=0, dx, dy;i<4;i++) {
		dx=x+d[i][0], dy=y+d[i][1];

		if (dx<n && dx>=0 && dy<n && dy>=0)
			if (map[dx][dy]=='r' && !vis[dx][dy] && visit(map, arr, dx, dy))
				return 1;
	}
	
	arr[x][y]=0;

	return 0;
}
