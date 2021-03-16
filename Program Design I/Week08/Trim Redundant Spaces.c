#include <stdio.h>

char ch, tmp;

int main() {

	while (~scanf("%c", &ch)) {
		if (ch=='\n') break;
		if (ch==' ' && tmp==' ') continue;
		printf("%c", (tmp=ch));
	}
}

