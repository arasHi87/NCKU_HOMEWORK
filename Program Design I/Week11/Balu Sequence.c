#include <stdio.h>
#define MOD 1000000007
#define int long long

int x;

int meow(int x) {
	if (x<=2) return 1;
	return (meow(x-1)*2+meow(x-2)*3)%MOD;
}

signed main() {
	scanf("%lld", &x);
	printf("%lld", meow(x));
}
