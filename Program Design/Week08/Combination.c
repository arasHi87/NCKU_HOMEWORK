#include <stdio.h>
#define int long long

int n, m, ans=1;

signed main() {
	scanf("%lld%lld", &m, &n);

	for (int i=1, j=n+1;i<=m-n;i++, j++)
		ans*=j, ans/=i;

	printf("%lld", ans);
}
