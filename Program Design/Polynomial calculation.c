#include <math.h>
#include <stdio.h>

float a;

int main() {
	scanf("%f", &a);
	printf("%0.1f", 7*pow(a, 4)-8*pow(a, 3)-pow(a, 2)+6*a-22);
}
