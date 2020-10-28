#include <stdio.h>

char ch;

int main() {
	while (~scanf("%c", &ch))
		if (ch=='A') printf("C");
		else if (ch=='B') printf("R");
		else if (ch=='C') printf("W");
		else if (ch=='D') printf("Z");
		else if (ch=='E') printf("G");
}

