#include <stdio.h>

int a, ans=0, tmp;

int fact(int x) {
	int res=1;
	
	for (int i=1;i<=x;i++)
		res*=i;

	return res;
}

int main() {
	scanf("%d", &a); tmp=a;

	while (tmp) ans+=fact(tmp%10), tmp/=10;

	if (ans==a) printf("%d is a strong number.", a);
	else printf("%d is not a strong number.", a);
}
