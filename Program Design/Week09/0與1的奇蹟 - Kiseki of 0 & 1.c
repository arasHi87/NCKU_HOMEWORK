#include <stdio.h>
#define maxN 40

int a[maxN], b[maxN], c[maxN];

int main() {
	for (int i=1;i<=32;i++) scanf("%d", a+i); 
	for (int i=1;i<=32;i++) scanf("%d", b+i);

	for (int i=32, tmp=0;i>=1;i--) {
		c[i]=a[i]^b[i]^tmp;
		tmp=(((a[i] ^ b[i]) && tmp) || (a[i] && b[i]));
	}
	
	for (int i=1;i<=32;i++)
		printf("%d ", c[i]);
}

/* #include <stdio.h> */
/* #define int long long */
/*  */
/* int a=0, b=0, c=0, idx=32, x, tmp[40]; */
/*  */
/* signed main() { */
/*     for (int i=1;i<=32;i++) { */
/*         scanf("%lld", &x); a|=x; a<<=1; */
/*     } */
/*  */
/*     for (int i=1;i<=32;i++) { */
/*         scanf("%lld", &x); b|=x; b<<=1; */
/*     } */
/*  */
/*     a>>=1, b>>=1, c=a+b; */
/*  */
/*     while (c) tmp[idx--]=c&1, c>>=1; */
/*  */
/*     for (int i=1;i<=32;i++) */
/*         printf("%lld ", tmp[i]); */
/* } */
