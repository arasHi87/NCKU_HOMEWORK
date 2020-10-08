#include <stdio.h>

int a, b;

int main() {
	scanf("%d%d", &a, &b);

	a+=(b>=10), b=(b>=10 ? b-10 : b+50);

	printf("%02d:%02d\n", a, b);
}
