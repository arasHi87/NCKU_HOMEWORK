#include <stdio.h>

int n, m;

int meow(int x, int y) {
	if (x==0) return y+1;
	if (y==0) return meow(x-1, 1);
	return meow(x-1, meow(x, y-1));
}

int main() {
	scanf("%d%d", &n, &m);
	printf("%d", meow(n, m));
}
