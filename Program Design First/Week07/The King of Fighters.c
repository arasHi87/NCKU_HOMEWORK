#include <stdio.h>

int a, b, c, idx=0;

int main() {
	scanf("%d%d", &a, &b);

	while (++idx) {
		scanf("%d", &c);

		idx&1 ? (b-=c) : (a-=c);

		if (idx&1 && b<=0) { printf("A"); break; }
		if (!(idx&1) && a<=0) { printf("B"); break; }
	}
}
