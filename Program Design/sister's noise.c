#include <stdio.h>

int n=10, ans=0, arr[15];

int max(int a, int b) { return a>b ? a : b; }
int abs(int x) { return x<0 ? x*-1 : x; }

int main() {
	for (int i=1;i<=n;i++)
		scanf("%d", arr+i);

	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)
			ans=max(ans, (arr[i]+arr[j])*abs(i-j));

	printf("%d", ans);
}
