#include <stdio.h>
#define maxN 25

int n, arr[maxN];

int main() {
	while (~scanf("%d%d%d", arr+1, arr+2, &n) && arr[1]+arr[2]+n) {
		for (int i=3;i<=n;i++)
			arr[i]=arr[i-1]+arr[i-2];
		
		n ? printf("%d", arr[n]) : printf(" ");
		
		puts("");
	}
}
