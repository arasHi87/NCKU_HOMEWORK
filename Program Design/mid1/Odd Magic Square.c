#include <stdio.h>
#include <string.h>
#define maxN 51

int n, x, y, arr[maxN][maxN];

int main() {
	scanf("%d", &n), x=1, y=(n+1)>>1;
	memset(arr, 0, sizeof arr);

	for (int i=1, tx, ty;i<=n*n;i++) {
		if (!arr[x][y]) { arr[x][y]=i; continue; }
		
		tx=x-1, ty=y+1;

		if (tx<1) tx=n;
		if (ty>n) ty=1;
		if (!arr[tx][ty]) { arr[tx][ty]=i, x=tx, y=ty; continue; }

		x+=1;

		if (x>n) x=1;

		arr[x][y]=i;
	}

	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++)
			printf("%d ", arr[i][j]);
		puts("");
	}
}
