#include <stdio.h>

int n, arr[1010][1010];

int main() {
	scanf("%d", &n);

	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d", &arr[i][j]);

	for (int i=1;i<=n-1;i++)
		for (int j=i+1;j<=n;j++)
			if (arr[i][j]!=arr[j][i])
			   return puts("No"); 

	puts("Yes");
}
