#include <stdio.h>
#include <string.h>
#define maxN 100010

int a, b, is_prime[maxN];

int main() {
	scanf("%d%d", &a, &b);
	memset(is_prime, 1, sizeof is_prime);

	is_prime[0]=is_prime[1]=0;

	for (int i=1;i<maxN;i++)
		if (is_prime[i])
			for (int j=i+i;j<maxN;j+=i)
				is_prime[j]=0;
	
	for (int i=a;i<=b;i++)
		if (is_prime[i])
			printf("%d ", i);
}
