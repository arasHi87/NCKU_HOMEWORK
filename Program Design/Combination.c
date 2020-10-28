#include <stdio.h>
#define int long long

int n, m, res1=1, res2=1;
int vis1[35], vis2[35];

signed main() {
	scanf("%lld%lld", &m, &n);

	for (int i=n+1;i<=m;i++) vis1[i]=1;
	for (int i=1;i<=m-n;i++) vis2[i]=1;
	for (int i=1;i<=m;i++)
		if (vis1[i] && vis2[i])
			vis1[i]=vis2[i]=0;
	for (int i=1;i<=m;i++)
		if (vis1[i]) res1*=i;
		else if (vis2[i]) res2*=i;

	printf("%lld", res1/res2);
}
