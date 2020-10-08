#include <stdio.h>

int a, b;

int main() {
	scanf("%d%d", &a, &b);
	
	a ^= b ^= a ^= b;
	
	printf("%d %d", a, b);
}
