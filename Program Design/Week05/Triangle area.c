#include <math.h>
#include <stdio.h>

float a, b, c, s;

int main() {
	scanf("%f%f%f", &a, &b, &c);

	s=(a+b+c)/2, s=sqrt(s*(s-a)*(s-b)*(s-c));

	printf("%0.2f", s);
}
