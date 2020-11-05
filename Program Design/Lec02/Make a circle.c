#include <stdio.h>

float a, PI=3.14;

int main() {
	scanf("%f", &a);
	printf("%0.2f %0.2f", a*a*PI, a*2*PI);
}
