#include <stdio.h>
#define int long long

int n, m;

int meow(int x, int y) {
	if (y==0 || x==y) return 1;
	return meow(x-1, y-1)+meow(x-1, y);
}

signed main() {
	scanf("%lld%lld", &n, &m);
	printf("%lld", meow(n, m));
}
