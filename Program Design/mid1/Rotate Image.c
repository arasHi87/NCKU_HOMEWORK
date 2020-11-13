#include <stdio.h>
#define maxN 105

int x, n, m;
int arr[maxN][maxN], tmp[maxN][maxN];

int main() {
	scanf("%d%d%d", &x, &n, &m);

	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d", &arr[i][j]);

	for (int i=90;i<=x;i+=90) {
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				tmp[j][n-i+1]=arr[i][j];

		n ^= m ^= n ^= m;

		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				arr[i][j]=tmp[i][j];
	}

	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++)
			printf("%d ", tmp[i][j]);
		puts("");
	}
}
