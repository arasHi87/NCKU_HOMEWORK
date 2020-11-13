#include <stdio.h>
#define maxN 10010

int n, m, arr[maxN];

int main() {
	scanf("%d%d", &n, &m), n+=m;

	for (int i=1, x;i<=n;i++)
		scanf("%d", &x), arr[x]=1;

	for (int i=1;i<=maxN;i++)
		if (arr[i])
			printf("%d ", i);
}
