#include <stdio.h>

int a, b, c;

int max(int x, int y) { return x>y ? x : y; }
int min(int x, int y) { return x<y ? x : y; }

int main() {
	scanf("%d%d%d", &a, &b, &c);
	printf("%d", min(max(a, b), c));
}
