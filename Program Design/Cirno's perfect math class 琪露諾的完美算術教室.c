#include <stdio.h>

int a, b, c, d;

int main() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	printf("%04d %04d %04d", a, a-b+c, a-b+c-d);
}
