#include <stdio.h>

int a;

int main() {
	scanf("%d", &a);

	if (a<1) printf("Calm");
	else if (a>=1 && a<=3) printf("Light air");
	else if (a>=4 && a<=27) printf("Breeze");
	else if (a>=28 && a<=47) printf("Gale");
	else if (a>=48 && a<=63) printf("Storm");
	else printf("Hurricane");
}
