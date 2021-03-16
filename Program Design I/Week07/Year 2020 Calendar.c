#include <stdio.h>

int n, day=3, cnt=1;
int dates[15]={0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
	scanf("%d", &n);
	puts("Sun Mon Tue Wed Thu Fri Sat ");

	for (int i=1;i<n;i++)
		for (int j=1;j<=dates[i];j++) {
			day+=1;

			if (day>7) day=1;
		}
	day++;

	if (day<=7) {
		for (int i=1;i<=7;i++) 
			i<day ? printf("    ") : printf("%3d ", cnt++);
		puts("");
	}

	for (int i=cnt, tmp=0;i<=dates[n];i++) {
		printf("%3d ", i); tmp++;

		if (tmp==7 && i!=dates[n]) puts(""), tmp=0;
	}
}
