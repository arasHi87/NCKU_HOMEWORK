#include <stdio.h>

int a;

int main() {
	scanf("%d", &a);

	for (int i=1;i<=a;i++) {
		for (int j=1;j<=a-i;j++) printf(" ");
		for (int j=1;j<=(i<<1)-1;j++) printf("*");
		puts("");
	}
}
