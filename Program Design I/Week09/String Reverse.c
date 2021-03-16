#include <stdio.h>

int n;
char arr[1010];

int main() {
	scanf("%d", &n); getchar();

	for (int i=1;i<=n;i++) scanf("%c", arr+i);
	for (int i=n;i>=1;i--) printf("%c", arr[i]);
}
