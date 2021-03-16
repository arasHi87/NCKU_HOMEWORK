#include <stdio.h>

long long a, b, c, sum=0, cnt=1, tmp, odd=0, even=0;

int main() {
	scanf("%lld%lld%lld", &a, &b, &c);

	sum=a*100000000000+b*100000+c;
	
	while (sum) {
		if (cnt&1) odd+=(sum%10)*3;
		else even+=sum%10;

		cnt++, sum/=10;
	}
	
	sum=10-(even+odd)%10;

	printf("%lld", sum==10 ? 0 : sum);
}
