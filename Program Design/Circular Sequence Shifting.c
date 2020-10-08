#include <stdio.h>

int n, x, a;

int main() {
	scanf("%d%d%d", &n, &x, &a);
	printf("%d", (x+a)%n);
}
