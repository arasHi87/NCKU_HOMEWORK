#include <stdio.h>

int k;
char ch;

int main() {
	scanf("%d", &k); getchar();
	
	k%=26, k+=26, k%=26;

	while (~scanf("%c", &ch)) {
		if (ch=='\n') continue;
		else if (ch>='a' && ch<='z') printf("%c", 'a'+(ch-'a'+k)%26);
		else if (ch>='A' && ch<='Z') printf("%c", 'A'+(ch-'A'+k)%26);
		else printf("%c", ch);
	}
}

