#include <math.h>
#include <stdio.h>
#define PI 3.14

double n, a, b, c;

int main() {
	scanf("%lf", &n);

	if (n==1) {
		scanf("%lf", &a);
		printf("%.2lf", a*a*a);
	}
	if (n==2) {
		scanf("%lf%lf%lf", &a, &b, &c);
		printf("%.2lf", a*b*c);
	}
	if (n==3) {
		scanf("%lf%lf", &a, &b);
		printf("%.2lf", PI*a*a*b);
	}
	if (n==4) {
		scanf("%lf", &a);
		printf("%.2lf", sqrt(2)/12*pow(a, 3)); 
	}
}
